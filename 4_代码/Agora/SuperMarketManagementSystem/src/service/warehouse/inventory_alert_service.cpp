#include <common/common_utils.hpp>
#include <common/uni_define.h>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/warehouse/inventory_alert_repository.h>
#include <service/warehouse/inventory_alert_service.h>

using json = nlohmann::json;

const std::vector<std::string> required_fields = {
    "goods_id",
    "lower_bound"
};

crow::response InventoryAlertService::create(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELDS(j, required_fields);

  auto &cache = GlobalIdCache::getInstance();

  auto inventory_alert_dto = InventoryAlertDTO::from_json(j);

  if (inventory_alert_dto.goods_rk_id == 0) return SET_ERR_RESPONSE(404, "Goods Not Found");

  auto result = InventoryAlertRepository::create(inventory_alert_dto);
  if (!result) return SET_ERR_RESPONSE(500, "DB_ERROR");

  nlohmann::json res {
      {"code", 201},
      {"data", {
          {"success", true},
          {"item", inventory_alert_dto}
        }
      }
  };

  return crow::response(201, res.dump());
}

// TODO: 必须添加一个 inventory id 暴露在外界
crow::response InventoryAlertService::updateByInventoryId(const std::string &body) {
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
