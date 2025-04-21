import os
import subprocess
import sys

DDL_ROOT = "sql"
OUTPUT_ROOT = "SuperMarketManagementSystem/include/model/db"
DDL2CPP_BIN = "/bin/sqlpp11-ddl2cpp"
NAMESPACE = "db"

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

def main():
    check_ddl2cpp()
    for ddl_file in find_ddl_files(DDL_ROOT):
        generate_header(ddl_file)

if __name__ == "__main__":
    main()
