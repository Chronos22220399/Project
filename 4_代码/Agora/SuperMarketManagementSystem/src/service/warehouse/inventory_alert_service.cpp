#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/warehouse/inventory_alert_repository.h>
#include <service/warehouse/inventory_alert_service.h>

using json = nlohmann::json;

crow::response InventoryAlertService::create(const std::string &body) {
  return crow::response(501, "Not implemented yet.");
}

crow::response InventoryAlertService::update(const std::string &body) {
  return crow::response(501, "Not implemented yet.");
}

crow::response InventoryAlertService::remove(const std::string &body) {
  return crow::response(501, "Not implemented yet.");
}

crow::response InventoryAlertService::getByPage(const std::string &body) {
  return crow::response(501, "Not implemented yet.");
}

crow::response InventoryAlertService::getAll() {
  return crow::response(501, "Not implemented yet.");
}
