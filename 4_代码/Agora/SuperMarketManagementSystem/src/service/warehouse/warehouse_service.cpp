#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/warehouse/warehouse_repository.h>
#include <service/warehouse/warehouse_service.h>

using json = nlohmann::json;

crow::response WarehouseService::create(const std::string &body) {
  return crow::response(200);
}

crow::response WarehouseService::getByPage(const std::string &body) {
  return crow::response(200);
}

crow::response WarehouseService::getAll() { return crow::response(200); }
