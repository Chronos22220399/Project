
#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/supplier/supplier_repository.h>
#include <service/supplier/supplier_service.h>

using json = nlohmann::json;

crow::response SupplierService::add(const std::string &body) {
  return crow::response(200);
}

crow::response SupplierService::getByPage(const std::string &body) {
  return crow::response(200);
}

crow::response SupplierService::getAll() { return crow::response(200); }
