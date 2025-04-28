// tools
#include <common/common_utils.hpp>
// third_party
#include <fmt/format.h>
#include <nlohmann/json.hpp>
// serv
#include <service/goods/inventory_service.h>
// repo
#include <repository/goods/goods_repository.h>
#include <repository/goods/inventory_repository.h>

using json = nlohmann::json;

const std::vector<std::string> required_fields = {"goods_rk_id", "warehouse_id",
                                                  "quantity"};

crow::response InventoryService::add(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELDS(j, required_fields);

  auto goods_rk_id = j.at("goods_id").get<id_type>();

  // 检测是否存在商品
  bool goods_not_exists = !GoodsRepository::existsById(goods_rk_id);
  if (goods_not_exists)
    return crow::response(404, "Goods not found.");

  auto inventory_dto = InventoryDTO::from_json(j);

  bool success = InventoryRepository::create(inventory_dto);
  return success ? crow::response(200) : crow::response(500);
}

crow::response InventoryService::getAll() {
  auto inventory_list = InventoryRepository::getAll();
  try {
    json res;
    res["success"] = true;
    res["total"] = inventory_list.size();
    res["data"] = inventory_list;

    return crow::response(200, res.dump());
  } catch (const std::exception &e) {
    LOG("Error: {}", e.what());
    return crow::response(500, fmt::format("Error: {}", e.what()));
  }
}

// method: GET
// params:
// page: int = default 1
// page_size: int = default 10
crow::response InventoryService::getByPage(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  int page = j.value("page", 1);
  int page_size = j.value("page_size", 10);
  if (page <= 0 || page_size <= 0) {
    return crow::response(400, "Invalid page or page_size");
  }

  // 分页查询
  auto offset = (page - 1) * page_size;

  try {
    // 获取货物总数
    count_type total = InventoryRepository::count();
    auto goods_list = InventoryRepository::getByPage(page_size, offset);

    json res;
    res["success"] = true;
    res["total"] = total;
    res["page"] = page;
    res["page_size"] = page_size;
    res["data"] = goods_list;

    return crow::response(200, res.dump());
  } catch (const std::exception &e) {
    LOG("Error: {}", e.what());
    return crow::response(500, fmt::format("Error: {}", e.what()));
  }
}
