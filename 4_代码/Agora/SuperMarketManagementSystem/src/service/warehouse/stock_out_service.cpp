#include <chrono>
#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/warehouse/stock_out_repository.h>
#include <service/warehouse/stock_out_service.h>

using json = nlohmann::json;
using namespace std::chrono;

ServiceResult StockOutService::create(StockOutDTO& dto)
{
  auto& cache = GlobalIdCache::getInstance();
  // 检查范围
  if (!utils::in(dto.status, StockOutDTO::status_domain)) {
    return {false, "Status out of range."};
  }
  if (!utils::in(dto.destination_type, StockOutDTO::destination_type_domain)) {
    return {false, "Destination reference out of range."};
  }

  if (dto.warehouse_rk_id == 0)
    return {false, "Warehouse not found."};
  if (dto.created_by == 0)
    return {false, "Employee not found."};

  dto.stock_out_id = utils::create_id("SO-");
  dto.created_at = time_point_cast<microseconds>(system_clock::now());

  // time_point_cast<microseconds>(system_clock::now());
  auto res = StockOutRepository::create(dto);
  if (!res)
    return {false, "Create stock out order failed."};

  cache.update("stock_out", dto.stock_out_id, res.value());
  return {true};
}

ServiceResult
StockOutService::updateByStockOutId(const std::string& stock_out_id,
                                    StockOutDTO& dto)
{
  auto& cache = GlobalIdCache::getInstance();
  // 检查范围
  if (!utils::in(dto.status, StockOutDTO::status_domain)) {
    return {false, "Status out of range."};
  }
  if (!utils::in(dto.destination_type, StockOutDTO::destination_type_domain)) {
    return {false, "Destination reference out of range."};
  }

  if (dto.warehouse_rk_id == 0)
    return {false, "Warehouse not found."};
  auto id = cache.getInternalId("stock_out", dto.stock_out_id);
  if (id == 0)
    return {false, "Stock out order cannot found."};

  auto success = StockOutRepository::updateById(id, dto);

  if (!success)
    return {false, "Update stock out order failed."};

  return {success};
}

ServiceResult
StockOutService::removeByStockOutId(const std::string& stock_out_id)
{
  auto& cache = GlobalIdCache::getInstance();
  auto id = cache.getInternalId("stock_out", stock_out_id);

  if (id == 0)
    return {false, "Stock out order cannot found."};

  bool success = StockOutRepository::removeById(id);

  if (!success)
    return {false, "Remove stock out order failed."};

  return {success};
}

ServiceResult StockOutService::getByPage(const int page, const int page_size)
{
  // 校验分页参数有效性
  if (page < 1 || page_size < 1) {
    return {false, "Invalid page or page_size"};
  }

  auto offset = (page - 1) * page_size;

  // 获取商品价格总数
  count_type total = StockOutRepository::count();
  auto stock_out_list = StockOutRepository::getByPage(page_size, offset);

  nlohmann::json data{{"success", true},
                      {"total", total},
                      {"page", page},
                      {"page_size", page_size},
                      {"items", stock_out_list}};

  return {true, "", data};
}

ServiceResult StockOutService::getAll()
{
  return {false, "Not implemented yet."};
}
