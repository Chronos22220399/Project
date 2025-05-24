curl -X POST "http://localhost:8080/api/goods_category/update" \
  -H "Content-Type: application/json" \
  -d '{
    "goods_category_id": "GCcc4f6d4f-437e-4d5e-a531-6eca7b0bff47",
    "goods_category_name": "心中类",
    "goods_category_description": "测试描述"
  }'
