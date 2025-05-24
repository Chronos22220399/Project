curl -X POST "http://localhost:8080/api/inventory/create" \
  -H "Content-Type: application/json" \
  -d '{
    "goods_id": "GCcc4f6d4f-437e-4d5e-a531-6eca7b0bff47",
    "warehouse_id": "0",
    "quantity": 100,
    "min_threshold": 10,
    "max_threshold": 85
  }'
