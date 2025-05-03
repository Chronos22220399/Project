#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/warehouse/warehouse_repository.h>
#include <service/warehouse/warehouse_service.h>

using json = nlohmann::json;

crow::response WarehouseService::create(const std::string &body) {
  return crow::response(501, "Not implemented yet.");
}

crow::response WarehouseService::getByPage(const std::string &body) {
  return crow::response(501, "Not implemented yet.");
}

crow::response WarehouseService::getAll() {
  auto warehouse_list = WarehouseRepository::getAll();
  try {
    json res;
    res["success"] = true;
    res["total"] = warehouse_list.size();
    res["data"] = warehouse_list;

    return crow::response(200, res.dump());
  } catch (const std::exception &e) {
    LOG("Error: {}", e.what());
    return crow::response(500, fmt::format("Error: {}", e.what()));
  }
}
