import re
import sys
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Tuple

# ========== 配置部分 ==========
PROJECT_ROOT = Path(__file__).parent.parent
DDL_DIR = PROJECT_ROOT / "sql"
DB_DIR = PROJECT_ROOT / "include/model/db"
DTO_DIR = PROJECT_ROOT / "include/model/dto"
REPO_DIR = PROJECT_ROOT / "include/repository"
SERVICE_DIR = PROJECT_ROOT / "include/service"
CONTROLLER_DIR = PROJECT_ROOT / "include/controller"
SRC_REPO_DIR = PROJECT_ROOT / "src/repository"
SRC_SERVICE_DIR = PROJECT_ROOT / "src/service"
SRC_CONTROLLER_DIR = PROJECT_ROOT / "src/controller"

TYPE_MAPPING = {
    "INTEGER": "in_id_type",
    "TEXT": "std::string",
    "VARCHAR": "std::string",
    "CHAR": "std::string",
    "REAL": "double",
    "FLOAT": "double",
    "NUMERIC": "double",
    "BOOLEAN": "bool",
    "BLOB": "std::vector<uint8_t>",
    "DATE": "datetime_type",
    "DATETIME": "datetime_type",
    "TIME": "time_type",
    "TIMESTAMP": "std::string"
}

DEFAULT_VALUES = {
    "in_id_type": "0",
    "std::string": '""',
    "double": "0.0",
    "bool": "false",
    "std::vector<uint8_t>": "{}",
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
        matchs = list(column_pattern.finditer(ddl))
        for match in matchs[1:]:
            name = match.group(1)
            data_type = match.group(2).upper()
            constraints = [c.upper() for c in match.group(3).split()]

            is_primary = "PRIMARY" in constraints
            is_foreign = "FOREIGN" in constraints
            is_unique = "UNIQUE" in constraints
            is_nullable = "NOT NULL" not in constraints

            # 防止底部的 FOREIGN 和 UNIQUE 被误认为是字段
            if name in ['FOREIGN', 'UNIQUE']:
                continue

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
        self.table_name_camel = to_camel_case(self.table['table_name'])
        self.table_name_snake = to_snake_case(self.table_name_camel)
        self.table_name = self.table['table_name']
        self.dto_name_camel = self.table_name_camel + "DTO"
        self.dto_name_snake = self.table_name_snake + "_dto"
        self.repo_name_camel = self.table_name_camel + "Repository"
        self.repo_name_snake = to_snake_case(self.repo_name_camel)
        self.service_name_camel = self.table_name_camel + "Service"
        self.service_name_snake = to_snake_case(self.service_name_camel)
        self.controller_name_camel = self.table_name_camel + "Controller"
        self.controller_name_snake = to_snake_case(self.controller_name_camel)

        print(f"{self.table_name}\n{self.dto_name_camel}\n"
              f"{self.dto_name_snake}\n{self.repo_name_camel}\n{self.repo_name_snake}\n{self.service_name_camel}\n"
              f"{self.service_name_snake}\n{self.controller_name_camel}\n{self.controller_name_snake}\n")

    # ---------- DTO生成 ----------
    def generate_dto(self, db_dir_name: str) -> str:
        fields = []
        for col in self.table["columns"]:
            cpp_type = TYPE_MAPPING.get(col["type"], "std::string")
            default = DEFAULT_VALUES.get(cpp_type, '{}')

            if col["is_primary"]:
                default = "0"  # 主键默认值
            elif col["is_foreign"]:
                default = "0"  # 外键默认值

            fields.append(f"{cpp_type} {col['name']} = {default};")

        return f"""#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/cache_func_getter.h>
#include <common/uni_define.h>
#include <model/db/{db_dir_name}/{self.table_name}.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for {self.table_name} table
struct {self.dto_name_camel}: public CacheFuncGetter {{

    {chr(10).join(fields)}

    // JSON serialization/deserialization
    static {self.dto_name_camel} from_json(const nlohmann::json& j) {{
        try {{
            return {self.dto_name_camel}{{
                {self._generate_from_json()}
            }};
        }} catch (const std::exception& e) {{
            std::cerr << "[from_json error] " << e.what() << "\\n"
                      << "Input JSON: " << j.dump(2) << std::endl;
            throw;
        }}
    }}
    
}};

inline void to_json(nlohmann::json &j, const {self.dto_name_camel}& {self.dto_name_snake}) {{
    j = nlohmann::json{{
        {self._generate_to_json()}
    }};
}}

// ORM mapping
namespace model {{
template <>
struct ReflectTable<{self.dto_name_camel}, db::{self.table_name}> {{
    static constexpr auto map_members = std::make_tuple(
        {self._generate_orm_mapping()}
    );
}};

// mapping
template <typename {self.table_name.capitalize()}Row> struct ReflectTableRow<{self.dto_name_camel}, {self.table['table_name'].capitalize()}Row> {{
    static {self.dto_name_camel} assign_model({self.table_name.capitalize()}Row &&row) {{
        return {self.dto_name_camel} {{
            {self._generate_orm_mapping_rev()}
        }};           
    }}
}};
}} // namespace model
"""

    def _generate_from_json(self) -> str:
        lines = []
        for col in self.table["columns"]:
            cpp_type = TYPE_MAPPING.get(col["type"], "std::string")
            if col["is_primary"]:
                continue  # 主键由数据库生成

            value_expr: str = f"j.at(\"{col['name']}\").get<{cpp_type}>(),"

            if col["type"] in ["DATE", "DATETIME"]:
                value_expr = f"utils::string_to_time(j.at(\"{col['name']}\").get<std::string>()),"
            lines.append(f".{col['name']} = {value_expr}")
        return '\n'.join(lines)

    def _generate_to_json(self) -> str:
        entries = []
        for col in self.table["columns"]:
            # 处理特殊类型（如日期需要格式化）
            value_expr = f"{self.dto_name_snake}.{col['name']}"
            if col["type"] in ["DATE", "DATETIME"]:
                value_expr = f"utils::time_to_string({self.dto_name_snake}.{col['name']})"

            entries.append(
                f'{{"{col["name"]}", {value_expr}}}'  # 正确闭合的格式化字符串
            )
        return ',\n'.join(entries)

    def _generate_orm_mapping(self) -> str:
        return ',\n'.join( f'std::make_pair(&{self.dto_name_camel}::{col["name"]}, '
                           f'&db::{self.table_name}::{col["name"]})'
                           for col in self.table["columns"]
                           )

    def _generate_orm_mapping_rev(self) -> str:
        # ret = ',\n'.join(f'.{col["name"]} = row.{col["name"]}' for col in self.table["columns"])
        ret = ""
        lines = []
        for col in self.table["columns"]:
            table_row_expr = f"row.{col["name"]}"
            dto_row_expr = f"{col["name"]}"
            # if col["type"] in ["DATE", "DATETIME"]:
            #     table_row_expr = f"utils::to_string({table_row_expr})"

            lines.append(
                f'.{dto_row_expr} = {table_row_expr}'
            )
        ret = ',\n'.join(lines)
        return ret

        # ---------- Repository生成 ----------
    def generate_repository(self, db_dir_name: str) -> Tuple[str, str]:
        h_content = f"""#pragma once
#include <model/dto/{db_dir_name}/{self.dto_name_snake}.hpp>
#include <common/generic_model.hpp>

class {self.repo_name_camel} : public model::GenericModel<{self.dto_name_camel}, db::{self.table_name}> {{
public:
    // CRUD Operations
    static insert_ret_type create(const {self.dto_name_camel}& {self.dto_name_camel});
    static select_ret_type<{self.dto_name_camel}> get(const std::string &{self.table_name_snake}_name);
    static update_ret_type updateById(const in_id_type id, const {self.dto_name_camel}& {self.dto_name_snake});
    static delete_ret_type removeById(const in_id_type id);
    
    // Custom Queries
    static select_ret_type<{self.dto_name_camel}> getAll();
    static select_ret_type<{self.dto_name_camel}> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    {self._generate_foreign_key_methods()}
}};
"""

        cpp_content = f"""#include <repository/{db_dir_name}/{self.repo_name_snake}.h>

using namespace model;

// CRUD Operations
insert_ret_type {self.repo_name_camel}::create(const {self.dto_name_camel} &{self.dto_name_snake}) {{
    return _insert({self.dto_name_snake});
}};

select_ret_type<{self.dto_name_camel}> {self.repo_name_camel}::get(const std::string& {self.table_name_snake}_name) {{
  return _select(db::{self.table_name}{{}}.{self.table_name_snake}_name == {self.table_name_snake}_name);
}};

update_ret_type {self.repo_name_camel}::update(const {self.dto_name_camel} &dto) {{
    return _update(dto, db::{self.table_name}{{}}.{self.table_name_snake}_id == dto.{self.table_name_snake}_id);
}};

delete_ret_type {self.repo_name_camel}::remove(const std::string& {self.table_name_snake}_id) {{
  return _remove(db::{self.table_name}{{}}.{self.table_name_snake}_id == {self.table_name_snake}_id);
}}

// Custom Queries
select_ret_type<{self.dto_name_camel}> {self.repo_name_camel}::getAll() {{
  return _select(db::{self.table_name}{{}}.id >= 0);
}}

select_ret_type<{self.dto_name_camel}> {self.repo_name_camel}::getByPage(int page_size,
                                                           int offset) {{
  return _select_from(db::{self.table_name}{{}}.id >= 0, page_size, offset);
}}

count_type {self.repo_name_camel}::count() {{ return _count(); }}

// 其他方法实现...
"""
        return h_content, cpp_content

    def _generate_foreign_key_methods(self) -> str:
        methods = []
        for fk in self.table["foreign_keys"]:
            ref_dto = to_camel_case(fk["ref_table"]) + "DTO"
            methods.append(
                f"static select_ret_type<{self.dto_name_camel}> "
                f"getBy{to_camel_case(fk['column'])}(in_id_type {fk['column']});"
            )
        return '\n    '.join(methods)

    # ---------- Controller生成 ----------
    def generate_controller(self, db_dir_name: str) -> Tuple[str, str]:
        h_content = f"""#pragma once
#include <crow.h>
#include <nlohmann/json.hpp>

class {self.controller_name_camel} {{
public:
    static void registerRoutes(crow::SimpleApp& app);
}};
"""

        cpp_content = f"""#include <controller/{db_dir_name}/{self.controller_name_snake}.h>
#include <service/{db_dir_name}/{self.service_name_snake}.h>

void {self.controller_name_camel}::registerRoutes(crow::SimpleApp& app) {{
    CROW_ROUTE(app, "/api/{self.table_name}/create")
        .methods("POST"_method)([](const crow::request& req) {{
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, {self.dto_name_camel}::required_fields);
            
            auto {self.dto_name_snake} = {self.dto_name_camel}::from_json(j);
            
            auto res = {self.service_name_camel}::create({self.dto_name_snake});
            return utils::to_response(res, 201);
        }});
        
    CROW_ROUTE(app, "/api/{self.table_name}/update")
        .methods("POST"_method)([](const crow::request& req) {{
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, {self.dto_name_camel}::required_fields);
            
            auto {self.dto_name_snake} = {self.dto_name_camel}::from_json(j);
            auto {self.table_name_snake}_id = {self.dto_name_snake}.{self.table_name_snake}_id;
            
            auto res = {self.service_name_camel}::updateBy{self.table_name_camel}Id({self.table_name_snake}_id, {self.dto_name_snake});
            return utils::to_response(res, 200);
        }});
        
    CROW_ROUTE(app, "/api/{self.table_name}/remove")
        .methods("POST"_method)([](const crow::request& req) {{
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);
            // 检查必填字段
            CHECK_REQUIRED_FIELD(j, "{self.table_name_snake}_id");
            
            auto {self.table_name_snake}_id = j.at("{self.table_name_snake}_id").get<ex_id_type>();
            
            auto res = {self.service_name_camel}::removeBy{self.table_name_camel}Id({self.table_name_snake}_id);
            
            return utils::to_response(res, 200);
        }});
        
    CROW_ROUTE(app, "/api/{self.table_name}/getByPage")
        .methods("POST"_method)([](const crow::request& req) {{
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);

            CHECK_REQUIRED_FIELD(j, "page");
            CHECK_REQUIRED_FIELD(j, "page_size");

            int page = j.value("page", 1);
            int page_size = j.value("page_size", 10);

            auto res = {self.service_name_camel}::getByPage(page, page_size);
            return utils::to_response(res, 200);
        }});
        
    CROW_ROUTE(app, "/api/{self.table_name}/getAll")
        .methods("GET"_method)([]() {{
            auto res = {self.service_name_camel}::getAll();
            return utils::to_response(res, 200);
        }});
        
    // 其他路由...
}}
"""
        return h_content, cpp_content

    def generate_service(self, db_dir_name: str, func_sig_list: list[str]):
        h_content = f"""#pragma once
#include <crow.h>
#include <string>

class {self.service_name_camel} {{
public:
    {self._generate_func_statement(func_sig_list)}
}};
"""

        cpp_content = f"""#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/{db_dir_name}/{self.repo_name_snake}.h>
#include <service/{db_dir_name}/{self.service_name_snake}.h>

using json = nlohmann::json;

{self._generate_func_defination(func_sig_list)}
"""
        return h_content, cpp_content;

    # 生成函数声明
    def _generate_func_statement(self, func_sig_list: list[str]):
        ret = ';\n'.join(func_sig_list) + ";"
        return ret;

    # 生成函数定义
    def _generate_func_defination(self, func_sig_list: list[str]):
        if len(func_sig_list) == 0:
            return ""

        func_define_list = []
        func_define: str = ""
        for func_sig in func_sig_list:
            if len(func_sig) == 0:
                continue

            func_info = func_sig.split(' ')
            _, ret_type, content = self._get_func_info(func_info)
            # 构造出函数定义
            func_define = ret_type + " " + f"{self.service_name_camel}" + "::" + content + " {\n\treturn {false, \"Not implemented yet.\"};\n }";

            func_define_list.append(func_define)
            func_define = "\n\n".join(func_define_list)

        return func_define

    def _get_func_info(self, func_info):
        specify_info = ""
        ret_type: str
        content: str
        if (func_info[0] == "static"):
            specify_info = func_info[0]
            ret_type = func_info[1]
            content = " ".join(func_info[2:])
        elif (func_info[0] == "inline"):
            ret_type = func_info[1]
            content = " ".join(func_info[2:])
        else:
            ret_type = func_info[0]
            content = " ".join(func_info[1:])

        return specify_info, ret_type, content


# ========== 文件操作 ==========
class FileManager:
    @staticmethod
    def backup(path: Path):
        if path.exists():
            backup_path = path.with_name(
                f"{path.stem}{path.suffix}.bak_{timestamp()}"
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
    db_dir_name = ddl_path.parent.name
    dto_content = generator.generate_dto(db_dir_name)
    dto_path = DTO_DIR / ddl_path.parent.name / f"{table_info['table_name']}_dto.hpp"
    FileManager.write_file(dto_path, dto_content)

    # 生成Repository
    repo_h, repo_cpp = generator.generate_repository(db_dir_name)
    repo_h_path = REPO_DIR / db_dir_name / f"{table_info['table_name']}_repository.h"
    repo_cpp_path = SRC_REPO_DIR / db_dir_name / f"{table_info['table_name']}_repository.cpp"
    FileManager.write_file(repo_h_path, repo_h)
    FileManager.write_file(repo_cpp_path, repo_cpp)

    # 生成Controller
    ctrl_h, ctrl_cpp = generator.generate_controller(db_dir_name)
    ctrl_h_path = CONTROLLER_DIR / db_dir_name / f"{table_info['table_name']}_controller.h"
    ctrl_cpp_path = SRC_CONTROLLER_DIR / db_dir_name / f"{table_info['table_name']}_controller.cpp"
    FileManager.write_file(ctrl_h_path, ctrl_h)
    FileManager.write_file(ctrl_cpp_path, ctrl_cpp)

    # 生成Service
    service_func_list = [
        "static ServiceResult create({} &dto)",
        "static ServiceResult update(const std::string &ex_id, {} &dto)",
        "static ServiceResult remove(const std::string &ex_id)",
        "static ServiceResult getByPage(const int page, const int page_size)",
        "static ServiceResult getAll()"
    ]
    srv_h, srv_cpp = generator.generate_service(db_dir_name, service_func_list)
    srv_h_path = SERVICE_DIR / db_dir_name / f"{table_info['table_name']}_service.h"
    srv_cpp_path = SRC_SERVICE_DIR / db_dir_name / f"{table_info['table_name']}_service.cpp"
    FileManager.write_file(srv_h_path, srv_h)
    FileManager.write_file(srv_cpp_path, srv_cpp)
