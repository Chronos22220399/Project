curl -X POST "http://localhost:8080/api/warehouse/create" \
  -H "Content-Type: application/json" \
  -d '{
    "warehouse_id": "1",
    "warehouse_name": "测试种类",
    "location": "测试描述",
    "capacity": 1000,
    "manager_id": "none",
    "phone": "1232424",
    "status": "active",
    "remark": "none"
  }'
