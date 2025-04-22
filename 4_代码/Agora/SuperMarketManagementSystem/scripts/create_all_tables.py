import os
import subprocess
import sys
import sqlite3

DDL_ROOT = "sql"
OUTPUT_ROOT = "include/model/db"
DDL2CPP_BIN = "/bin/sqlpp11-ddl2cpp"
NAMESPACE = "db"
SQLITE_DB_PATH = "datas/datas.sqlite3"

def check_ddl2cpp():
    if not os.path.exists(DDL2CPP_BIN):
        print(f"Error: ddl2cpp script not found at {DDL2CPP_BIN}")
        sys.exit(1)

def find_ddl_files(base_dir):
    for root, _, files in os.walk(base_dir):
        for file in files:
            if file.endswith(".ddl"):
                yield os.path.join(root, file)

def get_relative_subdir(file_path, base_dir):
    return os.path.relpath(os.path.dirname(file_path), base_dir)

def generate_header(ddl_file):
    relative_subdir = get_relative_subdir(ddl_file, DDL_ROOT)
    output_dir = os.path.join(OUTPUT_ROOT, relative_subdir)
    os.makedirs(output_dir, exist_ok=True)

    ddl_basename = os.path.splitext(os.path.basename(ddl_file))[0]
    output_path = os.path.join(output_dir, ddl_basename)

    cmd = [
        DDL2CPP_BIN,
        "-identity-naming",
        ddl_file,
        output_path,
        NAMESPACE
    ]

    print(f"Generating: {output_path}.h")
    subprocess.run(cmd, check=True)

def create_tables_in_sqlite(ddl_file):
    with open(ddl_file, 'r', encoding='utf-8') as f:
        ddl_sql = f.read()

    if not ddl_sql.strip():
        print(f"Warning: DDL file {ddl_file} is empty.")
        return

    print(f"Executing SQL for: {ddl_file}")
    try:
        conn = sqlite3.connect(SQLITE_DB_PATH)
        cursor = conn.cursor()
        cursor.executescript(ddl_sql)
        conn.commit()
        conn.close()
    except sqlite3.Error as e:
        print(f"SQLite error in {ddl_file}: {e}")
        sys.exit(1)

def main():
    check_ddl2cpp()
    for ddl_file in find_ddl_files(DDL_ROOT):
        generate_header(ddl_file)
        create_tables_in_sqlite(ddl_file)

if __name__ == "__main__":
    main()
