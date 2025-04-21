import os
import sys
import subprocess

DDL2CPP_BIN = "/bin/sqlpp11-ddl2cpp"
NAMESPACE = "db"
DDL_ROOT = "sql"
OUTPUT_ROOT = "SuperMarketManagementSystem/include/model/db"

def usage():
    print("Usage: python gen_single_header.py <relative/path/to/file.ddl>")
    sys.exit(1)

def check_ddl2cpp():
    if not os.path.exists(DDL2CPP_BIN):
        print(f"Error: ddl2cpp script not found at {DDL2CPP_BIN}")
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

    cmd = [
        DDL2CPP_BIN,
        "-identity-naming",
        full_path,
        output_path,
        NAMESPACE
    ]

    print(f"Generating: {output_path}.h")
    subprocess.run(cmd, check=True)

if __name__ == "__main__":
    main()
