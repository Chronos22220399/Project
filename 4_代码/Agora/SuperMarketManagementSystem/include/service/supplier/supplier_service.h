#pragma once
#include <crow.h>
#include <model/dto/supplier/supplier_dto.hpp>
#include <string>

class SupplierService {
  public:
  static ServiceResult create(SupplierDTO& dto);
  static ServiceResult updateBySupplierId(const std::string& ex_id,
                                        SupplierDTO& dto);
  static ServiceResult removeBySupplierId(const std::string& ex_id);
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getAll();
};
