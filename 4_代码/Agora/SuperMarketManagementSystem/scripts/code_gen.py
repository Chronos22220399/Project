import re
import sys
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Tuple

# ========== 配置部分 ==========
PROJECT_ROOT = Path(__file__).parent.parent
DDL_DIR = PROJECT_ROOT / "sql"
DTO_DIR = PROJECT_ROOT / "include/model/dto"
REPO_DIR = PROJECT_ROOT / "include/repository"
SERVICE_DIR = PROJECT_ROOT / "include/service"
CONTROLLER_DIR = PROJECT_ROOT / "include/controller"
SRC_REPO_DIR = PROJECT_ROOT / "src/repository"
SRC_SERVICE_DIR = PROJECT_ROOT / "src/service"
SRC_CONTROLLER_DIR = PROJECT_ROOT / "src/controller"

TYPE_MAPPING = {
    "INTEGER": "id_type",
    "TEXT": "std::string",
    "VARCHAR": "std::string",
    "CHAR": "std::string",
    "REAL": "double",
    "FLOAT": "double",
    "NUMERIC": "double",
    "BOOLEAN": "bool",
    "BLOB": "std::vector<uint8_t>",
    "DATE": "std::string",
    "DATETIME": "std::string",
    "TIMESTAMP": "std::string"
}

DEFAULT_VALUES = {
    "id_type": "0",
    "std::string": '""',
    "double": "0.0",
    "bool": "false",
    "std::vector<uint8_t>": "{}"
}

# ========== 工具函数 ==========
def to_camel_case(snake_str: str) -> str:
    components = snake_str.split('_')
    return ''.join(x.title() for x in components)

def to_snake_case(camel_str: str) -> str:
    return re.sub(r'(?<!^)(?=[A-Z])', '_', camel_str).lower()

def timestamp() -> str:
    return datetime.now().strftime("%Y%m%d_%H%M%S")

# ========== DDL解析器 ==========
class DDLAnalyzer:
    @staticmethod
    def parse(ddl: str) -> Dict:
        # 修改后（安全版本）
        table_match = re.search(
            r"CREATE TABLE (IF NOT EXISTS )?(\w+)", 
            ddl, 
            re.IGNORECASE
        )
        if not table_match:
            raise ValueError(f"DDL文件中未找到有效的表名: {ddl[:50]}...")
        table_name = table_match.group(2)  # 确保捕获第二个分组
        
        columns = []
        foreign_keys = []
        
        # 解析列定义
        column_pattern = re.compile(
            r"^\s*(\w+)\s+(\w+)\s*(.*?)(?=,|$)",
            re.MULTILINE | re.IGNORECASE
        )
        for match in column_pattern.finditer(ddl):
            name = match.group(1)
            data_type = match.group(2).upper()
            constraints = [c.upper() for c in match.group(3).split()]
            
            is_primary = "PRIMARY" in constraints
            is_foreign = "FOREIGN" in constraints
            is_unique = "UNIQUE" in constraints
            is_nullable = "NOT NULL" not in constraints
            
            columns.append({
                "name": name,
                "type": data_type,
                "is_primary": is_primary,
                "is_foreign": is_foreign,
                "is_unique": is_unique,
                "is_nullable": is_nullable
            })
        
        # 解析外键
        fk_pattern = re.compile(
            r"FOREIGN KEY\s*\((\w+)\)\s*REFERENCES\s*(\w+)\((\w+)\)",
            re.IGNORECASE
        )
        for match in fk_pattern.finditer(ddl):
            foreign_keys.append({
                "column": match.group(1),
                "ref_table": match.group(2),
                "ref_column": match.group(3)
            })
        
        return {
            "table_name": table_name,
            "columns": columns,
            "foreign_keys": foreign_keys
        }

# ========== 代码生成器 ==========
class CodeGenerator:
    def __init__(self, table_info: Dict):
        self.table = table_info
        self.dto_name = to_camel_case(self.table["table_name"]) + "DTO"
        self.repo_name = self.dto_name[:-3] + "Repository"
        self.service_name = self.dto_name[:-3] + "Service"
        self.controller_name = self.dto_name[:-3] + "Controller"
    
    # ---------- DTO生成 ----------
    def generate_dto(self) -> str:
        fields = []
        for col in self.table["columns"]:
            cpp_type = TYPE_MAPPING.get(col["type"], "std::string")
            default = DEFAULT_VALUES.get(cpp_type, '""')
            
            if col["is_primary"]:
                default = "0"  # 主键默认值
            elif col["is_foreign"]:
                default = "0"  # 外键默认值
                
            fields.append(f"{cpp_type} {col['name']} = {default};")
        
        return f"""#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <nlohmann/json.hpp>
#include <string>

// DTO for {self.table['table_name']} table
struct {self.dto_name} {{
    {chr(10).join(fields)}

    // JSON serialization/deserialization
    static {self.dto_name} from_json(const nlohmann::json& j) {{
        try {{
            return {self.dto_name}{{
                {self._generate_from_json()}
            }};
        }} catch (const std::exception& e) {{
            std::cerr << "[from_json error] " << e.what() << "\\n"
                      << "Input JSON: " << j.dump(2) << std::endl;
            throw;
        }}
    }}
    
    nlohmann::json to_json() const {{
        return {{
            {self._generate_to_json()}
        }};
    }}
}};

// ORM mapping
namespace model {{
template <>
struct ReflectTable<{self.dto_name}, db::{self.table['table_name']}> {{
    static constexpr auto map_members = std::make_tuple(
        {self._generate_orm_mapping()}
    );
}};
}} // namespace model
"""
    
    def _generate_from_json(self) -> str:
        lines = []
        for col in self.table["columns"]:
            if col["is_primary"]:
                continue  # 主键通常由数据库生成
            if col["name"] == "category_id":
                lines.append(f".category_id = utils::create_id(),")
            else:
                lines.append(f".{col['name']} = j.at(\"{col['name']}\"),")
        return '\n'.join(lines)
    
    def _generate_to_json(self) -> str:
        entries = []
        for col in self.table["columns"]:
            # 处理特殊类型（如日期需要格式化）
            value_expr = f"{col['name']}"
            if col["type"] in ["DATE", "DATETIME"]:
                value_expr = f"utils::format_datetime({col['name']})"
                
            entries.append(
                f'{{"{col["name"]}", {value_expr}}}'  # 正确闭合的格式化字符串
            )
        return ',\n'.join(entries)
    
    def _generate_orm_mapping(self) -> str:
        return ',\n'.join(
            f'std::make_pair(&{self.dto_name}::{col["name"]}, '
            f'&db::{self.table["table_name"]}::{col["name"]})'
            for col in self.table["columns"]
        )

    # ---------- Repository生成 ----------
    def generate_repository(self) -> Tuple[str, str]:
        hpp_content = f"""#pragma once
#include <model/dto/{self.table['table_name']}_dto.hpp>
#include <repository/generic_repository.hpp>

class {self.repo_name} : public GenericRepository<{self.dto_name}> {{
public:
    // CRUD Operations
    static insert_ret_type create(const {self.dto_name}& dto);
    static select_ret_type<{self.dto_name}> getById(id_type id);
    static update_ret_type update(const {self.dto_name}& dto);
    static delete_ret_type remove(id_type id);
    
    // Custom Queries
    static select_ret_type<std::vector<{self.dto_name}>> getAll();
    static select_ret_type<std::vector<{self.dto_name}>> paginate(int page, int size);
    static count_type count();
    
    // Foreign Key Relations
    {self._generate_foreign_key_methods()}
}};
"""
        
        cpp_content = f"""#include <repository/{to_snake_case(self.repo_name)}.hpp>

using namespace model;

insert_ret_type {self.repo_name}::create(const {self.dto_name}& dto) {{
    return GenericRepository<{self.dto_name}>::_insert(dto);
}}

select_ret_type<{self.dto_name}> {self.repo_name}::getById(id_type id) {{
    return GenericRepository<{self.dto_name}>::_get(id);
}}

// 其他方法实现...
"""
        return hpp_content, cpp_content

    def _generate_foreign_key_methods(self) -> str:
        methods = []
        for fk in self.table["foreign_keys"]:
            ref_dto = to_camel_case(fk["ref_table"]) + "DTO"
            methods.append(
                f"static select_ret_type<std::vector<{self.dto_name}>> "
                f"getBy{to_camel_case(fk['column'])}(id_type {fk['column']});"
            )
        return '\n    '.join(methods)

    # ---------- Controller生成 ----------
    def generate_controller(self) -> Tuple[str, str]:
        hpp_content = f"""#pragma once
#include <crow.h>
#include <service/{to_snake_case(self.service_name)}.hpp>

class {self.controller_name} {{
public:
    static void registerRoutes(crow::SimpleApp& app);
}};
"""
        
        cpp_content = f"""#include <controller/{to_snake_case(self.controller_name)}.hpp>

void {self.controller_name}::registerRoutes(crow::SimpleApp& app) {{
    CROW_ROUTE(app, "/api/{self.table['table_name']}/create")
        .methods("POST"_method)([](const crow::request& req) {{
            auto dto = {self.dto_name}::from_json(
                nlohmann::json::parse(req.body)
            );
            return {self.service_name}::create(dto).to_json().dump();
        }});
        
    CROW_ROUTE(app, "/api/{self.table['table_name']}/get/<int>")
        .methods("GET"_method)([](int id) {{
            return {self.service_name}::getById(id).to_json().dump();
        }});
        
    // 其他路由...
}}
"""
        return hpp_content, cpp_content

# ========== 文件操作 ==========
class FileManager:
    @staticmethod
    def backup(path: Path):
        if path.exists():
            backup_path = path.with_name(
                f"{path.stem}.bak_{timestamp()}{path.suffix}"
            )
            path.rename(backup_path)
            print(f"Backup created: {backup_path}")

    @staticmethod
    def write_file(path: Path, content: str):
        path.parent.mkdir(parents=True, exist_ok=True)
        FileManager.backup(path)
        with path.open("w", encoding="utf-8") as f:
            f.write(content)
        print(f"Generated: {path}")

# ========== 主流程 ==========
def process_ddl(ddl_path: Path, interactive: bool = True):
    with ddl_path.open("r") as f:
        ddl = f.read()
    
    table_info = DDLAnalyzer.parse(ddl)
    generator = CodeGenerator(table_info)
    
    # 生成DTO
    dto_content = generator.generate_dto()
    dto_path = DTO_DIR / ddl_path.parent.name / f"{table_info['table_name']}_dto.hpp"
    FileManager.write_file(dto_path, dto_content)
    
    # 生成Repository
    repo_hpp, repo_cpp = generator.generate_repository()
    repo_hpp_path = REPO_DIR / f"{table_info['table_name']}_repository.hpp"
    repo_cpp_path = SRC_REPO_DIR / f"{table_info['table_name']}_repository.cpp"
    FileManager.write_file(repo_hpp_path, repo_hpp)
    FileManager.write_file(repo_cpp_path, repo_cpp)
    
    # 生成Controller
    ctrl_hpp, ctrl_cpp = generator.generate_controller()
    ctrl_hpp_path = CONTROLLER_DIR / f"{table_info['table_name']}_controller.hpp"
    ctrl_cpp_path = SRC_CONTROLLER_DIR / f"{table_info['table_name']}_controller.cpp"
    FileManager.write_file(ctrl_hpp_path, ctrl_hpp)
    FileManager.write_file(ctrl_cpp_path, ctrl_cpp)

def main():
    interactive = "--auto" not in sys.argv
    for ddl_file in DDL_DIR.rglob("*.ddl"):
        if interactive:
            print(f"Process {ddl_file}? [Y/n/a] ")
            choice = input().lower()
            if choice == 'n':
                continue
            if choice == 'a':
                interactive = False
        process_ddl(ddl_file, interactive)

if __name__ == "__main__":
    main()
