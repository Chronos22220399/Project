import os
import sys
import subprocess
import sqlite3

DDL2CPP_BIN = "/bin/sqlpp11-ddl2cpp"
NAMESPACE = "db"
DDL_ROOT = "sql"
OUTPUT_ROOT = "SuperMarketManagementSystem/include/model/db"
SQLITE_DB_PATH = "SuperMarketManagementSystem/datas/datas.sqlite3"

def usage():
    print("Usage: python gen_single_header.py <relative/path/to/file.ddl>")
    sys.exit(1)

def check_ddl2cpp():
    if not os.path.exists(DDL2CPP_BIN):
        print(f"Error: ddl2cpp script not found at {DDL2CPP_BIN}")
        sys.exit(1)

def generate_header(full_path, output_path):
    cmd = [
        DDL2CPP_BIN,
        "-identity-naming",
        full_path,
        output_path,
        NAMESPACE
    ]
    print(f"Generating: {output_path}.h")
    subprocess.run(cmd, check=True)

def create_table_in_sqlite(ddl_file_path):
    print(f"Executing SQL: {ddl_file_path}")
    with open(ddl_file_path, 'r', encoding='utf-8') as f:
        ddl_sql = f.read()

    if not ddl_sql.strip():
        print("Warning: DDL file is empty.")
        return

    try:
        conn = sqlite3.connect(SQLITE_DB_PATH)
        cursor = conn.cursor()
        cursor.executescript(ddl_sql)
        conn.commit()
        conn.close()
    except sqlite3.Error as e:
        print(f"SQLite error: {e}")
        sys.exit(1)

def main():
    check_ddl2cpp()

    if len(sys.argv) != 2:
        usage()

    ddl_path = sys.argv[1]
    if not ddl_path.endswith(".ddl"):
        usage()

    full_path = os.path.join(DDL_ROOT, ddl_path)
    if not os.path.exists(full_path):
        print(f"Error: {full_path} does not exist")
        sys.exit(1)

    subdir = os.path.dirname(ddl_path)
    ddl_basename = os.path.splitext(os.path.basename(ddl_path))[0]
    output_dir = os.path.join(OUTPUT_ROOT, subdir)
    os.makedirs(output_dir, exist_ok=True)
    output_path = os.path.join(output_dir, ddl_basename)

    generate_header(full_path, output_path)
    create_table_in_sqlite(full_path)

if __name__ == "__main__":
    main()
