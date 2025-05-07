// tools
#include <common/common_utils.hpp>
#include <common/global_id_cache.hpp>
// repo
#include <repository/goods/goods_repository.h>
// service
#include <service/goods/goods_service.h>
// third_party
#include <fmt/format.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

const std::vector<std::string> required_fields = {
    "goods_name",      "category_id", "supplier_id", "unit_id",
    "shelf_life_days", "barcode",     "image_url",   "description"};

// MARK: create
crow::response GoodsService::create(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j); // 使用现有JSON解析宏

  CHECK_REQUIRED_FIELDS(j, required_fields);

  try {
    auto goods_dto = GoodsDTO::from_json(j);
    goods_dto.goods_id = utils::create_id("G"); // 生成外部ID

    if (GoodsRepository::create(goods_dto)) {
      json res = {{"code", 201},
                  {"data",
                   {{"goods_id", goods_dto.goods_id},
                    {"create_time", utils::get_current_iso8601()}}}};
      return crow::response(201, res.dump());
    }
    return crow::response(500,
                          json{{"code", 500}, {"error", "DB_ERROR"}}.dump());

  } catch (const std::exception &e) {
    return crow::response(500, json{{"code", 500}, {"error", e.what()}}.dump());
  }
}

crow::response GoodsService::getByPage(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELD(j, "page");
  CHECK_REQUIRED_FIELD(j, "page_size");

  int page = j.value("page", 1);
  int page_size = j.value("page_size", 10);
  if (page <= 0 || page_size <= 0) {
    return crow::response(400, "Invalid page or page_size");
  }

  // 分页查询
  auto offset = (page - 1) * page_size;

  try {
    // 获取分页数据
    count_type total = GoodsRepository::count();
    auto goods_list = GoodsRepository::getByPage(page_size, offset);

    json res;
    res["code"] = 200; // 使用状态码替代success布尔值
    res["data"] = {
        {"total", total},
        {"current_page", page},
        {"page_size", page_size},
        {"total_pages",
         static_cast<int>(std::ceil(total / static_cast<double>(page_size)))},
        {"items", goods_list} // 确保每个item中的id字段已转换为string类型
    };

    // 添加分页导航标识
    res["data"]["has_prev"] = (page > 1);
    res["data"]["has_next"] = (page * page_size < total);

    return crow::response(200, res.dump());

  } catch (const std::exception &e) {
    json error_res = {{"code", 500},
                      {"error", e.what()},
                      {"detail", fmt::format("Query failed: {}", e.what())}};
    return crow::response(500, error_res.dump());
  }
}

// MARK: read
crow::response GoodsService::getAll() {
  auto goods_list = GoodsRepository::getAll();
  try {
    json res;
    res["code"] = 200;
    res["data"] = {
        {"success", true}, {"total", goods_list.size()}, {"items", goods_list}};

    return crow::response(200, res.dump());
  } catch (const std::exception &e) {
    json error_res = {{"code", 500},
                      {"error", e.what()},
                      {"detail", fmt::format("Query failed: {}", e.what())}};
    return crow::response(500, error_res.dump());
  }
}

// MARK: 商品详细信息查询接口 - POST /api/goods/get_goods_detail_info_by_id
crow::response GoodsService::getGoodsDetailInfoById(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELD(j, "goods_id");

  auto goods_id = j.at("goods_id").get<std::string>();

  auto data = GoodsRepository::getGoodsDetailInfoByGoodsId(goods_id);

  try {
    json res;
    res["code"] = 200;
    res["data"] = {{"success", true}, {"total", data.size()}, {"items", data}};
    return crow::response(200, res.dump());
  } catch (const std::exception &e) {
    json error_res = {{"code", 500},
                      {"error", e.what()},
                      {"detail", fmt::format("Query failed: {}", e.what())}};
    return crow::response(500, error_res.dump());
  }
}
