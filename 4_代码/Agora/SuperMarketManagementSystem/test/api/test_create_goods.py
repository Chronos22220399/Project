import requests
import pytest
import json
import os

# 加载 JSON 文件
def load_test_cases(json_file_path):
    with open(json_file_path, 'r', encoding='utf-8') as f:
        return json.load(f)

# 参数化测试用例
@pytest.mark.parametrize("case_id, payload", [
    (str(k), v) for k, v in load_test_cases("./jsons/test_create_goods_cases.json").items()
])
def test_create_goods(case_id, payload):
    response = requests.post("http://localhost:8888/goods/add", json=payload)
    print(f"Case {case_id}: Status {response.status_code}, Response: {response.text}")
    assert response.status_code == 200
