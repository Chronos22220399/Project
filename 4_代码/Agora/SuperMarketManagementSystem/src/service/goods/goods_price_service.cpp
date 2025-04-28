#include <common/common_utils.hpp>
// third_party
#include <fmt/format.h>
#include <nlohmann/json.hpp>
// serv
#include <service/goods/goods_price_service.h>
// repo
#include <repository/goods/goods_price_repository.h>
#include <repository/goods/goods_repository.h>

using json = nlohmann::json;

const std::vector<std::string> required_fields = {"goods_id", "price",
                                                  "start_time"};

// Implemented
crow::response GoodsPriceService::add(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELDS(j, required_fields);

  auto goods_id = j.at("goods_id").get<id_type>();

  // 检查商品价格是否已存在，若存在则直接返回并告知原因，对于一个已存在的商品价格，我们只能查找、修改或删除
  bool price_exists = GoodsPriceRepository::exists(goods_id);
  if (price_exists)
    return crow::response(409, "Goods price already exists, you can only "
                               "modify or delete or query it.");

  // 检查商品是否已经存在，若不存在则返回
  bool goods_not_exists = !GoodsRepository::exists(goods_id);
  if (goods_not_exists)
    return crow::response(405, "Goods not found.");

  auto goods_price_dto = GoodsPriceDTO::from_json(j);

  bool success = GoodsPriceRepository::create(goods_price_dto);
  return success ? crow::response(200) : crow::response(500);
}

crow::response GoodsPriceService::update(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELDS(j, required_fields);

  auto goods_id = j.at("goods_id").get<id_type>();

  // 检查商品价格是否已存在，若不存在则直接返回并告知原因
  bool price_exists = GoodsPriceRepository::exists(goods_id);
  if (price_exists)
    return crow::response(404, "Goods price not found.");

  auto goods_price_dto = GoodsPriceDTO::from_json(j);

  bool success = GoodsPriceRepository::update(goods_price_dto);
  return success ? crow::response(200) : crow::response(500);
}

crow::response GoodsPriceService::remove(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  // 检测是否存在 goods_id 字段
  if (!j.contains("goods_id"))
    return crow::response(400, "Missing field: goods_id");

  id_type goods_id = j.at("goods_id").get<id_type>();

  // 检查是否存在 goods_id 所对应的商品价格
  bool price_not_exists = !GoodsPriceRepository::exists(goods_id);
  if (price_not_exists)
    return crow::response(404, "Goods price not found.");

  // 删除商品价格
  bool success = GoodsPriceRepository::remove_by_goods_id(goods_id);
  return success ? crow::response(200) : crow::response(500);
}

// Not implemented
crow::response GoodsPriceService::getByPage(const std::string &body) {
  return crow::response(501, "Not implemented yet.");
}

crow::response GoodsPriceService::getAll() {
  return crow::response(501, "Not implemented yet.");
}
