curl -X POST "http://localhost:8080/api/warehouse/set_status" \
  -H "Content-Type: application/json" \
  -d '{
    "warehouse_id": "1",
    "status": "active"
  }'
