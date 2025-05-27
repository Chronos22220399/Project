#pragma once
#include <crow.h>
#include <string>
#include <model/dto/supplier/supplier_contract_dto.hpp>

class SupplierContractService {
  public:
  static ServiceResult create(SupplierContractDTO& dto);
  static ServiceResult updateBySupplierContractId(const std::string& ex_id,
                                                  SupplierContractDTO& dto);
  static ServiceResult removeBySupplierContractId(const std::string& ex_id);
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getAll();
};
