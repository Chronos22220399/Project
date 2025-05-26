curl -X POST "http://localhost:8080/api/stock_out/create" \
  -H "Content-Type: application/json" \
  -d '{
    "stock_out_id": "OUT20231001",
    "warehouse_id": "W-54d7dade-7251-4e54-8bc1-1df33327c1fd",
    "created_at": "2023-10-10T14:30:00Z",
    "created_by": "EMP1001",
    "destination_type": "sale",
    "destination_reference": 0,
    "status": "pending",
    "remark": "测试出库单"
  }'
