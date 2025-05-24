#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/warehouse/stock_in_repository.h>
#include <service/warehouse/stock_in_service.h>
#include <common/common_utils.hpp>

using json = nlohmann::json;
using namespace std::chrono;

ServiceResult StockInService::create(StockInDTO& dto)
{
  auto &cache = GlobalIdCache::getInstance();

  // 存在性检验
  if (dto.warehouse_rk_id == 0)
    return {false, "Warehouse doesn't exists."};
  if (dto.created_by == 0)
    return {false, "Employee doesn't exists."};
  if (!utils::in(dto.source_type, StockInDTO::type_domain))
    return {false, "Source type not in domain."};

  // 添加入库信息
  dto.stock_in_id = utils::create_id("SI-");
  // 设置创建时间
  dto.created_at = time_point_cast<microseconds>(system_clock::now());

  auto res = StockInRepository::create(dto);
  if (!res.has_value()) {
    return {false, "Create stock in order failed."};
  }

  cache.update("stock_in", dto.stock_in_id, dto.id);
  return {true};
}

ServiceResult StockInService::updateByStockInId(const std::string& ex_id,
                                                StockInDTO& dto)
{
  return {false, "Not implemented yet."};
}

ServiceResult StockInService::removeByStockInId(const std::string& stock_in_id)
{
  return {false, "Not implemented yet."};
}

ServiceResult StockInService::getByPage(const int page, const int page_size)
{
  return {false, "Not implemented yet."};
}

ServiceResult StockInService::getAll()
{
  return {false, "Not implemented yet."};
}
