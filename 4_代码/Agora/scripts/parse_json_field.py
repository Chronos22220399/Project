#!/usr/bin/env python3
import json
import sys

def query_json(data, query: str):
    """执行类似 jq 的字段查询，如 '.user.name'"""
    keys = query.strip('.').split('.')
    for key in keys:
        if isinstance(data, dict) and key in data:
            data = data[key]
        else:
            print(f"[Error] 无法解析字段：{key}", file=sys.stderr)
            sys.exit(1)
    return data

def main():
    if len(sys.argv) != 3:
        print("用法: python json_query.py '.field.path' file.json", file=sys.stderr)
        sys.exit(1)

    query, file_path = sys.argv[1], sys.argv[2]

    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
    except Exception as e:
        print(f"[Error] 打开或解析 JSON 文件失败：{e}", file=sys.stderr)
        sys.exit(1)

    result = query_json(data, query)
    if isinstance(result, (dict, list)):
        print(json.dumps(result, ensure_ascii=False, indent=2))
    else:
        print(result)

if __name__ == '__main__':
    main()
