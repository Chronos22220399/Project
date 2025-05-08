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
// tools
#include <common/global_id_cache.hpp>

using json = nlohmann::json;

const std::vector<std::string> required_fields = {"goods_id", "warehouse_id",
                                                  "quantity"};

// MARK: 库存-创建服务
//
// @param body - 请求体（JSON字符串），包含 goods_id, warehouse_id, quantity
// @return crow::response
//   成功: 201, 仅返回 code 字段
//   失败: 400, JSON解析或字段缺失
//         404, 商品或仓库不存在
//         500, 数据库插入异常
crow::response InventoryService::create(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  // 检查必填字段
  CHECK_REQUIRED_FIELDS(j, required_fields);

  auto goods_id = j.at("goods_id").get<ex_id_type>();
  auto warehouse_id = j.at("warehouse_id").get<ex_id_type>();
  auto quantity = j.at("quantity").get<long int>();

  auto &cache = GlobalIdCache::getInstance();
  auto goods_rk_id = cache.getInternalId("goods", goods_id);
  auto warehouse_rk_id = cache.getInternalId("warehouse", warehouse_id);

  // 检查商品和仓库是否存在
  if (!goods_rk_id) {
    return SET_ERR_RESPONSE(404, "Goods not found.");
  }
  if (!warehouse_rk_id) {
    return SET_ERR_RESPONSE(404, "Warehouse not found.");
  }

  // 创建库存记录
  auto inventory_dto = InventoryDTO{.goods_rk_id = goods_rk_id,
                                    .warehouse_rk_id = warehouse_rk_id,
                                    .quantity = quantity};

  bool success = InventoryRepository::create(inventory_dto).has_value();
  return success ? SET_EMPTY_DATA_RESPONSE(201)
                 : SET_ERR_RESPONSE(500, "DB_INSERT_ERROR");
}

// MARK: 库存-更新服务
//
// @param body - 请求体（JSON字符串），包含 goods_id, warehouse_id, quantity
// @return crow::response
//   成功: 200, 仅返回 code 字段
//   失败: 400, JSON解析或字段缺失
//         404, 商品或仓库不存在
//         500, 数据库更新异常
crow::response InventoryService::updateByGoodsId(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  // 检查必填字段
  CHECK_REQUIRED_FIELDS(j, required_fields);

  auto inventory_dto = InventoryDTO::from_json(j);

  // 检查商品和仓库是否存在
  if (!inventory_dto.goods_rk_id) {
    return SET_ERR_RESPONSE(404, "Goods not found.");
  }
  if (!inventory_dto.warehouse_rk_id) {
    return SET_ERR_RESPONSE(404, "Warehouse not found.");
  }

  // 更新库存记录
  bool success = InventoryRepository::updateByGoodsRKId(
      inventory_dto.goods_rk_id, inventory_dto);
  return success ? SET_EMPTY_DATA_RESPONSE(200)
                 : SET_ERR_RESPONSE(500, "DB_UPDATE_ERROR");
}

// MARK: 库存-根据商品ID查询服务
//
// @param body - 请求体（JSON字符串），包含 goods_id
// @return crow::response
//   成功: 200, JSON 包含库存记录信息（含success, total, data）
//   失败: 400, JSON解析或字段缺失
//         404, 商品不存在
//         500, 数据库查询异常
crow::response InventoryService::getByGoodsId(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELD(j, "goods_id");
  auto goods_id = j.at("goods_id").get<ex_id_type>();

  auto &cache = GlobalIdCache::getInstance();
  auto goods_rk_id = cache.getInternalId("goods", goods_id);

  if (!goods_rk_id) {
    return SET_ERR_RESPONSE(404, "Goods not found.");
  }

  try {
    auto inventory_list = InventoryRepository::getByGoodsRKId(goods_rk_id);

    nlohmann::json data{{"success", true},
                        {"total", inventory_list.size()},
                        {"items", inventory_list}};

    return SET_SUC_DATA_RESPONSE(data);

  } catch (const std::exception &e) {
    return SET_ERR_RESPONSE(500, e.what());
  }
}

// MARK: 库存-根据仓库ID查询服务
//
// @param body - 请求体（JSON字符串），包含 warehouse_id
// @return crow::response
//   成功: 200, JSON 包含库存记录信息（含success, total, data）
//   失败: 400, JSON解析或字段缺失
//         404, 仓库不存在
//         500, 数据库查询异常
crow::response InventoryService::getByWarehouseId(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELD(j, "warehouse_id");
  auto warehouse_id = j.at("warehouse_id").get<ex_id_type>();

  auto &cache = GlobalIdCache::getInstance();
  auto warehouse_rk_id = cache.getInternalId("warehouse", warehouse_id);

  if (!warehouse_rk_id) {
    return SET_ERR_RESPONSE(404, "Warehouse not found.");
  }

  try {
    auto inventory_list =
        InventoryRepository::getByWarehouseRKId(warehouse_rk_id);

    nlohmann::json data{{"success", true},
                        {"total", inventory_list.size()},
                        {"items", inventory_list}};

    return SET_SUC_DATA_RESPONSE(data);
  } catch (const std::exception &e) {
    return SET_ERR_RESPONSE(500, e.what());
  }
}

// MARK: 库存-分页查询服务
//
// @param body - 请求体（JSON字符串），包含 page 和 page_size，默认值为 1 和 10
// @return crow::response
//   成功: 200, JSON 包含分页后的库存记录信息（含success, total, page,
//   page_size, data） 失败: 400, 分页参数非法; 500, 数据库查询异常
crow::response InventoryService::getByPage(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  // 获取分页参数并设置默认值
  int page = j.value("page", 1);
  int page_size = j.value("page_size", 10);

  // 校验分页参数有效性
  if (page <= 0 || page_size <= 0) {
    return SET_ERR_RESPONSE(400, "Invalid page or page_size");
  }

  auto offset = (page - 1) * page_size;

  try {
    // 获取库存记录总数
    count_type total = InventoryRepository::count();
    auto inventory_list = InventoryRepository::getByPage(page_size, offset);

    nlohmann::json data{{"success", true},
                        {"total", total},
                        {"page", page},
                        {"page_size", page_size},
                        {"items", inventory_list}};

    return SET_SUC_DATA_RESPONSE(data);

  } catch (const std::exception &e) {
    return SET_ERR_RESPONSE(500, e.what());
  }
}

// Not implement !
crow::response InventoryService::getAll() {
  return crow::response(501, "Not implement yet.");
}
