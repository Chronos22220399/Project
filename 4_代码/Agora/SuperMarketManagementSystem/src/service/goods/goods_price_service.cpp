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
                                                  "start_time", "note"};

// Implemented
// MARK: create
crow::response GoodsPriceService::create(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELDS(j, required_fields);

  auto goods_price_dto = GoodsPriceDTO::from_json(j);

  if (goods_price_dto.goods_rk_id == 0)
    return crow::response(404, "Goods not found.");

  // 检查商品价格是否已存在，若存在则直接返回并告知原因，对于一个已存在的商品价格，我们只能查找、修改或删除
  bool price_exists =
      GoodsPriceRepository::existsByGoodsRKId(goods_price_dto.goods_rk_id);
  if (price_exists)
    return crow::response(409, "Goods price already exists, you can only "
                               "modify or delete or query it.");

  // 检查商品是否已经存在，若不存在则返回
  bool goods_not_exists =
      !GoodsRepository::existsById(goods_price_dto.goods_rk_id);
  if (goods_not_exists)
    return crow::response(405, "Goods not found.");

  bool success = GoodsPriceRepository::create(goods_price_dto);
  return success ? crow::response(200) : crow::response(500);
}

// MARK: update
crow::response GoodsPriceService::updateByGoodsId(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELDS(j, required_fields);

  auto goods_price_dto = GoodsPriceDTO::from_json(j);
  if (goods_price_dto.goods_rk_id == 0)
    return crow::response(404, "Goods not found.");

  // 检查商品价格是否已存在，若不存在则直接返回并告知原因
  bool price_exists =
      GoodsPriceRepository::existsByGoodsRKId(goods_price_dto.goods_rk_id);
  if (price_exists)
    return crow::response(404, "Goods price not found.");

  bool success = GoodsPriceRepository::updateByGoodsRKId(
      goods_price_dto.goods_rk_id, goods_price_dto);
  return success ? crow::response(200) : crow::response(500);
}

// MARK: delete
crow::response GoodsPriceService::removeByGoodsId(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  // 检测是否存在 goods_id 字段
  CHECK_REQUIRED_FIELD(j, "goods_id");
  auto goods_id = j.at("goods_id").get<std::string>();

  auto &cache = GlobalIdCache::getInstance();
  auto goods_rk_id = cache.getInternalId("goods", goods_id);

  if (goods_rk_id == 0)
    return crow::response(404, "Goods not found.");

  // 检查是否存在 goods_rk_id 所对应的商品价格
  bool price_not_exists = !GoodsPriceRepository::existsByGoodsRKId(goods_rk_id);
  if (price_not_exists)
    return crow::response(404, "Goods price not found.");

  // 删除商品价格
  bool success = GoodsPriceRepository::removeByGoodsRKId(goods_rk_id);
  return success ? crow::response(200) : crow::response(500);
}

// MARK: getByPage
crow::response GoodsPriceService::getByPage(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  // 解析分页参数并设置默认值
  int page = j.value("page", 1);
  int page_size = j.value("page_size", 10);

  // 校验分页参数有效性
  if (page < 1 || page_size < 1) {
    return crow::response(400, "Invalid page or page_size");
  }

  auto offset = (page - 1) * page_size;

  try {
    // 获取货物总数
    count_type total = GoodsPriceRepository::count();
    auto goods_price_list = GoodsPriceRepository::getByPage(page_size, offset);

    json res;
    res["success"] = true;
    res["total"] = total;
    res["page"] = page;
    res["page_size"] = page_size;
    res["data"] = goods_price_list;

    return crow::response(200, res.dump());
  } catch (const std::exception &e) {
    LOG("Error: {}", e.what());
    return crow::response(500, fmt::format("Error: {}", e.what()));
  }
}

// Not implemented
crow::response GoodsPriceService::getAll() {
  return crow::response(501, "Not implemented yet.");
}
