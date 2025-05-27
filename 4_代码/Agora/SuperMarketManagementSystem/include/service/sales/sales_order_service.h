#pragma once
#include <crow.h>
#include <model/dto/sales/sales_order_dto.hpp>
#include <string>

class SalesOrderService {
  public:
  static ServiceResult create(SalesOrderDTO& dto);
  static ServiceResult updateBySalesOrderId(const std::string& ex_id,
                                            SalesOrderDTO& dto);
  static ServiceResult removeBySalesOrderId(const std::string& ex_id);
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getAll();
};
