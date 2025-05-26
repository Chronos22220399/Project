#pragma once
#include <crow.h>
#include <model/dto/warehouse/stock_out_dto.hpp>
#include <string>
// sqlpp11
// controller -> service -> repository -> model/dto -> model/db -> database

class StockOutService {
  public:
  static ServiceResult create(StockOutDTO& dto);
  static ServiceResult updateByStockOutId(const std::string& ex_id,
                                          StockOutDTO& dto);
  static ServiceResult removeByStockOutId(const std::string& ex_id);
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getAll();
};
