curl -X POST "http://localhost:8080/api/inventory/get_by_goods_id" \
  -H "Content-Type: application/json" \
  -d '{
    "goods_id": "G-13d308c1-4384-44fd-90a8-3fce88dedda9"
  }'
