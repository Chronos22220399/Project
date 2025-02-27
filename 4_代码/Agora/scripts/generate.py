from pathlib import Path
import sqlite3
import subprocess


def find_path(cur_path: Path, tg_name: str) -> Path:
    if cur_path.name not in [tg_name]:
        res = list(cur_path.rglob(tg_name))
        return res[0]
    else:
        return cur_path
    
def get_datas_inner_dirs(sub_project_name: str) -> tuple[Path, Path, Path]:
    cur_path = Path().cwd()
    sub_project_path = find_path(cur_path, sub_project_name)
    datas_path = find_path(sub_project_path, "datas/")
    return datas_path / "ddls", datas_path / "include", datas_path / "sqlite3"

def generate_sqlite3_by_ddl(ddls_dir: Path, include_dir: Path, db_file_dir: Path, db_file_name: str, src_file_name: str):
    """ 根据 ddl 生成对应的 .sqlite3 文件和 .h 文件"""
    ddl_file = ddls_dir / f"{src_file_name}.ddl"
    cap_file_name = src_file_name.capitalize()
    include_file = include_dir / f"{src_file_name}"
    db_file = db_file_dir / f"{db_file_name}.sqlite3"
    
    # 生成 sql
    with open(ddl_file, "r", encoding="utf-8") as file: 
        sqls = file.readlines()
        sql = ""
        for sentence in sqls:
            sql += sentence
            
        with sqlite3.connect(database=str(db_file)) as conn:
            try:
                cursor = conn.cursor()
                cursor.execute(sql)
                conn.commit()
            except sqlite3.OperationalError as e:
                print(f"{e}")
                pass

    # 生成头文件
    script_path = Path().home()
    subprocess.run([script_path / ".install/bin/sqlpp11-ddl2cpp", ddl_file, include_file, cap_file_name])



if __name__ == "__main__":
    sub_project = input("请输入项目名: ")
    ddl = input("请输入 ddl 文件名: ")
    ddls_path, include_path, sqlite3_path = get_datas_inner_dirs(sub_project)
    print(ddls_path, include_path, sqlite3_path)
    
    generate_sqlite3_by_ddl(ddls_path, include_path, sqlite3_path, "datas", ddl)
