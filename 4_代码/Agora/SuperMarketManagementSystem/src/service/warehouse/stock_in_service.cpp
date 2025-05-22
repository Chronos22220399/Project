#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/warehouse/stock_in_repository.h>
#include <service/warehouse/stock_in_service.h>

using json = nlohmann::json;

ServiceResult StockInService::create(StockInDTO& dto)
{
  return {false, "Not implemented yet."};
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
