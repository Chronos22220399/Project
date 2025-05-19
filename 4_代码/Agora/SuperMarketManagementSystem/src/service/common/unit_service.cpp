// third_party
#include <fmt/format.h>
#include <nlohmann/json.hpp>
// repos
#include <repository/common/unit_repository.h>
// services
#include <service/common/unit_service.h>
// tools
#include <common/common_utils.hpp>
#include <common/global_id_cache.hpp>

using json = nlohmann::json;

static const std::vector<std::string> required_fields = {
    "unit_name", // 单位名称
};

crow::response UnitService::create(const std::string &body) {
  return utils::safeJsonExecution(body, [](const nlohmann::json &j) {
    CHECK_REQUIRED_FIELDS(j, required_fields);

    auto &cache = GlobalIdCache::getInstance();
    auto unit_dto = UnitDTO::from_json(j);
    unit_dto.unit_id = utils::create_id("U-");

    if (UnitRepository::_exists(db::unit{}.unit_name == unit_dto.unit_name)) {
      return SET_ERR_RESPONSE(302, "Unit name created");
    }

    if (auto id = UnitRepository::create(unit_dto); id) {
      cache.update("unit", unit_dto.unit_id, id.value());
      nlohmann::json data{unit_dto};
      return SET_SUC_DATA_RESPONSE(data);
    }

    return SET_ERR_RESPONSE(500, "DB ERROR");
  });
}

crow::response UnitService::updateByUnitId(const std::string &body) {
  return utils::safeJsonExecution(body, [](const nlohmann::json &j) {
    CHECK_REQUIRED_FIELDS(j, required_fields);
    CHECK_REQUIRED_FIELD(j, "unit_id");

    auto &cache = GlobalIdCache::getInstance();
    auto unit_id = j.at("unit_id").get<ex_id_type>();

    auto id = cache.getInternalId("unit", unit_id);

    if (id == 0) {
      return SET_ERR_RESPONSE(404, "Goods category not found.");
    }

    auto goods_category_dto = UnitDTO::from_json(j);

    bool success = UnitRepository::updateById(id, goods_category_dto);

    return success ? SET_EMPTY_DATA_RESPONSE(200)
                   : SET_ERR_RESPONSE(500, "DB_UPDATE_ERROR");
  });
}

crow ::response UnitService::removeByUnitId(const std::string &body) {
  return utils::safeJsonExecution(body, [](const nlohmann::json &j) {
    CHECK_REQUIRED_FIELD(j, "unit_id");

    auto unit_id = j.at("unit_id").get<ex_id_type>();

    auto &cache = GlobalIdCache::getInstance();
    auto id = cache.getInternalId("unit", unit_id);

    if (id == 0) {
      return SET_ERR_RESPONSE(404, "Unit not found.");
    }

    bool success = UnitRepository::removeById(id);

    if (success) {
      cache.invalidate("unit", unit_id);
      return SET_EMPTY_DATA_RESPONSE(200);
    }
    return SET_ERR_RESPONSE(500, "DB_DELETE_ERROR");
  });
}

crow::response UnitService::getByPage(const std::string &body) {
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
    count_type total = UnitRepository::count();
    auto unit_list = UnitRepository::getByPage(page_size, offset);

    json data{
        {"total", total},
        {"current_page", page},
        {"page_size", page_size},
        {"total_pages",
         static_cast<int>(std::ceil(total / static_cast<double>(page_size)))},
        {"items", unit_list}, // 确保每个item中的id字段已转换为string类型
    };

    return SET_SUC_DATA_RESPONSE(data);

  } catch (const std::exception &e) {
    return SET_ERR_RESPONSE(500, e.what());
  }
}

crow::response UnitService::getAll() {
  auto unit_list = UnitRepository::getAll();
  try {
    json data{
        {"success", true}, {"total", unit_list.size()}, {"items", unit_list}};

    return SET_SUC_DATA_RESPONSE(data);
  } catch (const std::exception &e) {
    return SET_ERR_RESPONSE(500, e.what());
  }
}
