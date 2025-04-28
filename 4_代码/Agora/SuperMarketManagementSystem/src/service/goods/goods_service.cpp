#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/goods/goods_repository.h>
#include <service/goods/goods_service.h>

using json = nlohmann::json;

const std::vector<std::string> required_fields = {
    "goods_name",      "category_rk_id", "supplier_rk_id", "unit_rk_id",
    "shelf_life_days", "barcode",        "image_url",      "description"};

crow::response GoodsService::add(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELDS(j, required_fields);

  auto goods_dto = GoodsDTO::from_json(j);
  goods_dto.goods_id = utils::create_id("G");

  bool success = GoodsRepository::create(goods_dto);
  return success ? crow::response(200) : crow::response(500);
}

crow::response GoodsService::getAll() {
  auto goods_list = GoodsRepository::getAll();
  try {
    json res;
    res["success"] = true;
    res["total"] = goods_list.size();
    res["data"] = goods_list;

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
crow::response GoodsService::getByPage(const std::string &body) {
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
    count_type total = GoodsRepository::count();
    auto goods_list = GoodsRepository::getByPage(page_size, offset);

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

// id_type goods_id;
// std::string goods_name;
// id_type quantity;
// std::string unit;
// id_type warehouse_id;
// std::string warehouse_name;
// std::string location;
// date_cnt_type shelf_life_days;
crow::response GoodsService::getGoodsDetailInfoById(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELD(j, "goods_id");

  auto goods_id = j.at("goods_id").get<std::string>();

  auto data = GoodsRepository::getGoodsDetailInfoByGoodsId(goods_id);

  json res;
  res["success"] = true;
  res["total"] = data.size();
  res["data"] = data;

  return crow::response(200, res);
}
