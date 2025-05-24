#pragma once
#include <crow.h>
#include <model/dto/warehouse/stock_in_dto.hpp>
#include <string>


class StockInService {
  public:
  static ServiceResult create(StockInDTO& dto);
  static ServiceResult updateByStockInId(const std::string& ex_id,
                                         StockInDTO& dto);
  static ServiceResult removeByStockInId(const std::string& ex_id);
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getAll();
};
