import requests
import pytest
import json

def load_test_cases(json_file_path):
    with open(json_file_path, 'r', encoding='utf-8') as f:
        return json.load(f)

@pytest.mark.parametrize("case_id, payload", [
    (str(k), v) for k, v in load_test_cases("./jsons/test_get_goods.json").items()
])
def test_get_goods_by_page(case_id, payload):
    url = "http://localhost:8888/goods/get"
    headers = {'Content-Type': 'application/json'}

    print(f"\n=== Case {case_id} ===")
    try:
        if isinstance(payload, str):
            response = requests.post(url, data=payload, headers=headers)
        else:
            response = requests.post(url, json=payload, headers=headers)

        print(f"Status: {response.status_code}")

        if response.status_code == 200:
            data = response.json()
            goods_list = data.get("data", [])
            print(f"Returned {len(goods_list)} goods")
            for g in goods_list[:3]:  # 只打印前 3 个
                print(f"- ID: {g.get('goods_id', 'N/A')}, Name: {g.get('goods_name', 'N/A')}")
        else:
            print(f"Error Response: {response.text}")

        assert response.status_code in [200, 400, 500]
    except Exception as e:
        print(f"Exception occurred: {e}")
        assert False
