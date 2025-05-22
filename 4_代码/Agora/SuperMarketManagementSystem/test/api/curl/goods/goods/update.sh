curl -X POST "http://localhost:8080/api/goods/update" \
  -H "Content-Type: application/json" \
  -d '{
    "goods_id": "",
    "goods_category_id": "1",
    "supplier_id": "1",
    "unit_id": "1",
    "goods_name": "coke",
    "shelf_life_days": 180,
    "barcode": "1234567890123",
 "image_url":"12",
    "description": "测试描述"
  }'
