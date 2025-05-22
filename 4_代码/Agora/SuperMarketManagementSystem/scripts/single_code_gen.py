# single_code_gen.py

import sys
import os
from code_generator import process_ddl

def main():
    if len(sys.argv) != 2:
        print("Usage: python single_code_gen.py <path/to/file.ddl>")
        sys.exit(1)

    ddl_path = sys.argv[1]

    if not os.path.isfile(ddl_path):
        print(f"[ERROR] File not found: {ddl_path}")
        sys.exit(1)

    try:
        result = process_ddl(ddl_path)
        print(f"[SUCCESS] Generated module: {result['module']}")
    except Exception as e:
        print(f"[ERROR] Code generation failed: {e}")