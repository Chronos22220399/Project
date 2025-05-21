// tools
#include <common/common_utils.hpp>
// third_party
#include <fmt/format.h>
#include <nlohmann/json.hpp>
// stl
#include <chrono>
// serv
#include <service/goods/inventory_service.h>
// repo
#include <repository/goods/goods_repository.h>
#include <repository/goods/inventory_repository.h>
// tools
#include <common/global_id_cache.hpp>

using namespace std::chrono;

// MARK: 库存-创建服务
// 中间表无需注册到全局缓存中
ServiceResult InventoryService::create(InventoryDTO& inventory_dto)
{
  // 检查商品和仓库是否存在
  if (!inventory_dto.goods_rk_id) {
    return {false, "Goods not found."};
  }
  if (!inventory_dto.warehouse_rk_id) {
    return {false, "Warehouse not found."};
  }

  // 获取当前时间作为更新时间
  inventory_dto.last_updated =
    time_point_cast<microseconds>(system_clock::now());
  auto res = InventoryRepository::create(inventory_dto);

  if (!res.has_value())
    return {false, "Create goods failed", {}};

  return {true};
}

// MARK: 库存-更新服务
//
// @param body - 请求体（JSON字符串），包含 goods_id, warehouse_id, quantity
// @return crow::response
//   成功: 200, 仅返回 code 字段
//   失败: 400, JSON解析或字段缺失
//         404, 商品或仓库不存在
//         500, 数据库更新异常
ServiceResult InventoryService::updateByGoodsId(const in_id_type goods_rk_id,
                                                InventoryDTO& inventory_dto)
{
  // 检查商品和仓库是否存在
  if (!inventory_dto.goods_rk_id) {
    return {false, "Goods not found."};
  }
  if (!inventory_dto.warehouse_rk_id) {
    return {false, "Warehouse not found."};
  }

  inventory_dto.last_updated =
    time_point_cast<microseconds>(system_clock::now());
  // 更新库存记录
  bool success = InventoryRepository::updateByGoodsRKId(
    inventory_dto.goods_rk_id, inventory_dto);

  if (!success) {
    return {false, "Update inventory failed."};
  }
  return {true};
}


// MARK: 库存-根据商品ID查询服务
//
// @param body - 请求体（JSON字符串），包含 goods_id
// @return crow::response
//   成功: 200, JSON 包含库存记录信息（含success, total, data）
//   失败: 400, JSON解析或字段缺失
//         404, 商品不存在
//         500, 数据库查询异常
ServiceResult InventoryService::getByGoodsId(const std::string& goods_id)
{
  auto& cache = GlobalIdCache::getInstance();
  auto goods_rk_id = cache.getInternalId("goods", goods_id);

  if (!goods_rk_id) {
    return {false, "Goods not found."};
  }

  auto inventory_list = InventoryRepository::getByGoodsRKId(goods_rk_id);

  nlohmann::json data{{"success", true},
                      {"total", inventory_list.size()},
                      {"items", inventory_list}};

  return {true, "", data};
}

// MARK: 库存-根据仓库ID查询服务
//
// @param body - 请求体（JSON字符串），包含 warehouse_id
// @return crow::response
//   成功: 200, JSON 包含库存记录信息（含success, total, data）
//   失败: 400, JSON解析或字段缺失
//         404, 仓库不存在
//         500, 数据库查询异常
ServiceResult
InventoryService::getByWarehouseId(const std::string& warehouse_id)
{
  auto& cache = GlobalIdCache::getInstance();
  auto warehouse_rk_id = cache.getInternalId("warehouse", warehouse_id);

  if (!warehouse_rk_id) {
    return {false, "Warehouse not found."};
  }

  auto inventory_list =
    InventoryRepository::getByWarehouseRKId(warehouse_rk_id);

  nlohmann::json data{{"success", true},
                      {"total", inventory_list.size()},
                      {"items", inventory_list}};

  return {true, data};
}

// MARK: 库存-分页查询服务
//
// @param body - 请求体（JSON字符串），包含 page 和 page_size，默认值为 1 和 10
// @return crow::response
//   成功: 200, JSON 包含分页后的库存记录信息（含success, total, page,
//   page_size, data） 失败: 400, 分页参数非法; 500, 数据库查询异常
ServiceResult InventoryService::getByPage(const int page, const int page_size)
{
  // 校验分页参数有效性
  if (page <= 0 || page_size <= 0) {
    return {false, "Invalid page or page_size"};
  }

  auto offset = (page - 1) * page_size;

  // 获取库存记录总数
  count_type total = InventoryRepository::count();
  auto inventory_list = InventoryRepository::getByPage(page_size, offset);

  nlohmann::json data{{"success", true},
                      {"total", total},
                      {"page", page},
                      {"page_size", page_size},
                      {"items", inventory_list}};

  return {true, "", data};
}

// Not implement !
ServiceResult InventoryService::getAll()
{
  return {false, "Not implement yet."};
}
