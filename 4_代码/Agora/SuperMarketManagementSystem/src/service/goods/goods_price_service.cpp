#include <common/common_utils.hpp>
#include <common/uni_define.h>
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
// MARK: 商品价格-创建服务
//
// @param body - 请求体（JSON字符串），包含 goods_id, price, start_time, note
// @return crow::response
//   成功: 200, 仅返回 code 字段
//   失败: 400, JSON解析或字段缺失
//         404, 商品不存在
//         405, 商品未找到（逻辑检查）
//         409, 商品价格已存在
//         500, 数据库插入异常
crow::response GoodsPriceService::create(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELDS(j, required_fields);

  auto goods_price_dto = GoodsPriceDTO::from_json(j);

  if (goods_price_dto.goods_rk_id == 0) {
    return SET_ERR_RESPONSE(404, "Goods not found.");
  }

  // 检查商品价格是否已存在，若存在则返回冲突错误
  if (GoodsPriceRepository::existsByGoodsRKId(goods_price_dto.goods_rk_id)) {
    return SET_ERR_RESPONSE(409, "Goods price already exists. You can only "
                                 "modify, delete, or query it.");
  }

  // 检查商品是否存在，若不存在则返回
  if (!GoodsRepository::existsById(goods_price_dto.goods_rk_id)) {
    return SET_ERR_RESPONSE(405, "Goods not found.");
  }

  // 创建商品价格
  bool success = GoodsPriceRepository::create(goods_price_dto).has_value();
  return success ? SET_EMPTY_DATA_RESPONSE(200)
                 : SET_ERR_RESPONSE(500, "DB_INSERT_ERROR");
}

// MARK: 商品价格-删除服务
//
// @param body - 请求体（JSON字符串），包含 goods_id
// @return crow::response
//   成功: 200, 仅返回 code 字段
//   失败: 400, JSON解析或字段缺失
//         404, 商品不存在或商品价格不存在
//         500, 数据库删除异常
crow::response GoodsPriceService::removeByGoodsId(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  // 检查必填字段
  CHECK_REQUIRED_FIELD(j, "goods_id");
  auto goods_id = j.at("goods_id").get<ex_id_type>();

  auto &cache = GlobalIdCache::getInstance();
  auto goods_rk_id = cache.getInternalId("goods", goods_id);

  if (goods_rk_id == 0) {
    return SET_ERR_RESPONSE(404, "Goods not found.");
  }

  // 检查是否存在与 goods_rk_id 对应的商品价格
  if (!GoodsPriceRepository::existsByGoodsRKId(goods_rk_id)) {
    return SET_ERR_RESPONSE(404, "Goods price not found.");
  }

  // 删除商品价格
  bool success = GoodsPriceRepository::removeByGoodsRKId(goods_rk_id);
  return success ? SET_EMPTY_DATA_RESPONSE(200)
                 : SET_ERR_RESPONSE(500, "DB_DELETE_ERROR");
}

// MARK: 商品价格-更新服务
//
// @param body - 请求体（JSON字符串），包含 goods_id, price, start_time, note
// @return crow::response
//   成功: 200, 仅返回 code 字段
//   失败: 400, JSON解析或字段缺失
//         404, 商品不存在或商品价格不存在
//         500, 数据库更新异常
crow::response GoodsPriceService::updateByGoodsId(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  // 检查必填字段
  CHECK_REQUIRED_FIELDS(j, required_fields);

  auto goods_price_dto = GoodsPriceDTO::from_json(j);
  if (goods_price_dto.goods_rk_id == 0) {
    return SET_ERR_RESPONSE(404, "Goods not found.");
  }

  // 检查商品价格是否存在，若不存在则返回错误
  if (!GoodsPriceRepository::existsByGoodsRKId(goods_price_dto.goods_rk_id)) {
    return SET_ERR_RESPONSE(404, "Goods price not found.");
  }

  // 更新商品价格
  bool success = GoodsPriceRepository::updateByGoodsRKId(
      goods_price_dto.goods_rk_id, goods_price_dto);
  return success ? SET_EMPTY_DATA_RESPONSE(200)
                 : SET_ERR_RESPONSE(500, "DB_UPDATE_ERROR");
}

// MARK: 商品价格-分页查询服务
//
// @param body - 请求体（JSON字符串），可选包含 page, page_size 字段
// @return crow::response
//   成功: 200, JSON 包含分页后的商品价格信息（含success, total, page,
//   page_size, data） 失败: 400, 分页参数非法; 500, 数据库查询异常
crow::response GoodsPriceService::getByPage(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  // 解析分页参数并设置默认值
  int page = j.value("page", 1);
  int page_size = j.value("page_size", 10);

  // 校验分页参数有效性
  if (page < 1 || page_size < 1) {
    return SET_ERR_RESPONSE(400, "Invalid page or page_size");
  }

  auto offset = (page - 1) * page_size;

  try {
    // 获取商品价格总数
    count_type total = GoodsPriceRepository::count();
    auto goods_price_list = GoodsPriceRepository::getByPage(page_size, offset);

    nlohmann::json data{{"success", true},
                        {"total", total},
                        {"page", page},
                        {"page_size", page_size},
                        {"items", goods_price_list}};

    return SET_SUC_DATA_RESPONSE(data);
  } catch (const std::exception &e) {
    return SET_ERR_RESPONSE(500, e.what());
  }
}

// Not implemented !
crow::response GoodsPriceService::getAll() {
  return crow::response(501, "Not implemented yet.");
}
