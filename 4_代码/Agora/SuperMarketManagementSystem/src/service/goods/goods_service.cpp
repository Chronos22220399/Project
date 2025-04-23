#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/goods/goods_repository.h>
#include <service/goods/goods_service.h>

using json = nlohmann::json;

const std::vector<std::string> required_fields = {
    "goods_name",      "category_id", "supplier_id", "unit_id",
    "shelf_life_days", "barcode",     "image_url",   "description"};

crow::response GoodsService::add(const std::string &body) {
  auto j_opt = utils::try_parse_json(body);
  if (!j_opt)
    return crow::response(400, "Invalid JSON");
  const json &j = j_opt.value();

  for (const auto &field : required_fields) {
    if (!j.contains(field)) {
      return crow::response(400, "Missing field: " + field);
    }
  }

  bool success = GoodsRepository::create(GoodsDTO::from_json(j));
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
  auto j_opt = utils::try_parse_json(body);
  if (!j_opt)
    return crow::response(400, "Invalid JSON");
  const json &j = j_opt.value();

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
