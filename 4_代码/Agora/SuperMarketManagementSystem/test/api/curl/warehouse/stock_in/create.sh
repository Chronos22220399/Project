curl -X POST "http://localhost:8080/api/stock_in/create" \
  -H "Content-Type: application/json" \
  -d '{
    "stock_in_id": "SI-",
    "warehouse_id": "W-961efbb5-340a-4a52-aad6-4a6047af012d",
    "created_by": "测试描述",
    "capacity": 1000,
    "source_type": "none",
    "remark": "none"
  }'
