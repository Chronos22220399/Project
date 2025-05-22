curl -X POST "http://localhost:8080/api/goods_category/create" \
  -H "Content-Type: application/json" \
  -d '{
    "goods_category_id": "1",
    "goods_category_name": "测试种类",
    "goods_category_description": "测试描述"
  }'
