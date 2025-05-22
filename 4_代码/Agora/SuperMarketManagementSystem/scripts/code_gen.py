import os
import sys
from code_generator import process_ddl, DDL_DIR

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
