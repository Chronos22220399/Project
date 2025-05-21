#pragma once
#include <crow.h>
#include <model/dto/warehouse/warehouse_dto.hpp>
#include <string>

class WarehouseService {
  public:
  static ServiceResult create(WarehouseDTO& body);
  static ServiceResult updateByWarehouseId(const std::string& warehouse_id,
                                           const WarehouseDTO& warehouse_dto);
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult setStatus(const std::string& warehouse_id,
                                 const std::string& status);
  // static ServiceResult removeByWarehouseId(const std::string& warehouse_id);
  // static ServiceResult getAll();
};
