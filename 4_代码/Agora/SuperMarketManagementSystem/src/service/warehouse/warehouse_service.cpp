// third_party
#include <fmt/format.h>
#include <nlohmann/json.hpp>
// repos
#include <repository/warehouse/warehouse_repository.h>
// services
#include <service/warehouse/warehouse_service.h>
// tools
#include <common/common_utils.hpp>
#include <common/global_id_cache.hpp>

using json = nlohmann::json;

const std::vector<std::string> required_fields = {
    "warehouse_id",    // 仓库唯一标识
    "warehouse_name",  // 仓库名称
    "location",        // 地理位置
    "total_slots",     // 总货位数
    "available_slots", // 可用货位数
    "manager",         // 负责人
    "description"      // 仓库描述
};

crow::response WarehouseService::create(const std::string &body) {
  nlohmann::json j;

  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELDS(j, required_fields);

  try {
    auto warehouse_dto = WarehouseDTO::from_json(j);
    // 获取外部 id
    warehouse_dto.warehouse_id = utils::create_id("W-");
    // 插入数据到数据库
    auto insert_res = WarehouseRepository::create(warehouse_dto);

    if (!insert_res.has_value())
      return SET_ERR_RESPONSE(500, "DB_ERROR");

    auto &cache = GlobalIdCache::getInstance();
    cache.update("warehouse", warehouse_dto.warehouse_id, insert_res.value());

    nlohmann::json ret{{"code", 201}, {"data", warehouse_dto}};

    return crow::response(201, ret.dump());
  } catch (const std::exception &e) {
    return SET_ERR_RESPONSE(500, e.what());
  }
}

crow::response WarehouseService::updateByWarehouseId(const std::string &body) {
  // 检查并获取 json 内容
  return utils::safeJsonExecution(body, [](const nlohmann::json &j) {
    CHECK_REQUIRED_FIELDS(j, required_fields);
    auto warehouse_dto = WarehouseDTO::from_json(j);
    auto &cache = GlobalIdCache::getInstance();
    auto id = cache.getInternalId("warehouse", warehouse_dto.warehouse_id);

    if (id == 0 || !WarehouseRepository::existsById(id))
      return SET_ERR_RESPONSE(404, "Warehouse Not Found.");

    bool success = WarehouseRepository::updateById(id, warehouse_dto);
    return success ? SET_EMPTY_DATA_RESPONSE(200)
                   : SET_ERR_RESPONSE(500, "DB_UPDATE_ERROR");
  });
}

crow::response WarehouseService::removeByWarehouseId(const std::string &body) {
  return utils::safeJsonExecution(body, [](const nlohmann::json &j) {
    CHECK_REQUIRED_FIELD(j, "warehouse_id");
    auto warehouse_id = j.at("warehouse_id").get<ex_id_type>();

    auto &cache = GlobalIdCache::getInstance();
    auto id = cache.getInternalId("warehouse", warehouse_id);

    if (id == 0 || !WarehouseRepository::existsById(id))
      return SET_ERR_RESPONSE(404, "Warehouse Not Found.");

    bool success = WarehouseRepository::removeById(id);
    return success ? SET_EMPTY_DATA_RESPONSE(200)
                   : SET_ERR_RESPONSE(500, "DB_UPDATE_ERROR");
  });
}

crow::response WarehouseService::getByPage(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELD(j, "page");
  CHECK_REQUIRED_FIELD(j, "page_size");

  int page = j.value("page", 1);
  int page_size = j.value("page_size", 10);
  if (page <= 0 || page_size <= 0) {
    return SET_ERR_RESPONSE(400, "Invalid page or page_size");
  }

  // 分页查询
  auto offset = (page - 1) * page_size;

  try {
    // 获取分页数据
    count_type total = WarehouseRepository::count();
    auto warehouse_list = WarehouseRepository::getByPage(page_size, offset);

    json data{
        {"total", total},
        {"current_page", page},
        {"page_size", page_size},
        {"total_pages",
         static_cast<int>(std::ceil(total / static_cast<double>(page_size)))},
        {"items", warehouse_list}, // 确保每个item中的id字段已转换为string类型
    };

    return SET_SUC_DATA_RESPONSE(data);

  } catch (const std::exception &e) {
    return SET_ERR_RESPONSE(500, e.what());
  }
}

crow::response WarehouseService::getAll() {
  auto warehouse_list = WarehouseRepository::getAll();
  try {
    json data{{"success", true},
              {"total", warehouse_list.size()},
              {"items", warehouse_list}};

    return SET_SUC_DATA_RESPONSE(data);
  } catch (const std::exception &e) {
    return SET_ERR_RESPONSE(500, e.what());
  }
}
