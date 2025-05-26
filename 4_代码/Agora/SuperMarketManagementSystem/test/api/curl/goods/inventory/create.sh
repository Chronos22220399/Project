curl -X POST "http://localhost:8080/api/inventory/create" \
  -H "Content-Type: application/json" \
  -d '{
    "goods_id": "G-170e622d-550f-4ac9-8004-9f02f14fe746",
    "warehouse_id": "W-54d7dade-7251-4e54-8bc1-1df33327c1fd",
    "quantity": 100,
    "min_threshold": 10,
    "max_threshold": 85
  }'
