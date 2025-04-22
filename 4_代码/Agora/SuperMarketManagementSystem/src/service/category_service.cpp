#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/goods_category_repository.h>
#include <service/goods_category_service.h>

using json = nlohmann::json;

const std::vector<std::string> required_fields = {
    "category_name", "category_description", "parent_category_id"};

crow::response GoodsCategoryService::addCategory(const std::string &body) {
  auto j_opt = utils::try_parse_json(body);
  if (!j_opt)
    return crow::response(400, "Invalid JSON");
  const json &j = j_opt.value();

  for (const auto &field : required_fields) {
    if (!j.contains(field)) {
      return crow::response(400, "Missing field: " + field);
    }
  }

  bool success =
      GoodsCategoryRepository::insert(GoodsCategoryDTO::from_json(j));
  return success ? crow::response(200) : crow::response(500);
}

// method: GET
// params:
// page: int = default 1
// page_size: int = default 10
crow::response
GoodsCategoryService::getCategoryByPage(const std::string &body) {
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
    count_type total = GoodsCategoryRepository::count();
    auto goods_category_list =
        GoodsCategoryRepository::getCategoryByPage(page_size, offset);
    json res;
    res["success"] = true;
    res["total"] = total;
    res["page"] = page;
    res["page_size"] = page_size;
    res["data"] = goods_category_list;

    return crow::response(200, res.dump());
  } catch (const std::exception &e) {
    LOG("Error: {}", e.what());
    return crow::response(500, fmt::format("Error: {}", e.what()));
  }
}

crow::response GoodsCategoryService::getAllCategory() {
  auto goods_category_list = GoodsCategoryRepository::getAllCategory();
  try {
    json res;
    res["success"] = true;
    res["total"] = goods_category_list.size();
    res["data"] = goods_category_list;

    return crow::response(200, res.dump());
  } catch (const std::exception &e) {
    LOG("Error: {}", e.what());
    return crow::response(500, fmt::format("Error: {}", e.what()));
  }
}
