curl -X POST "http://localhost:8080/api/inventory/get_by_page" \
  -H "Content-Type: application/json" \
  -d '{
    "page": 1,
    "page_size": 2
  }'
