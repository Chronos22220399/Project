#pragma once
#include <common/common_utils.hpp>
#include <crow.h>
#include <model/dto/common/unit_dto.hpp>
#include <nlohmann/json.hpp>
#include <string>

class UnitService {
  public:
  static ServiceResult create(const UnitDTO& unit_dto);
  static ServiceResult updateByUnitId(const std::string& unit_id,
                                      const UnitDTO& unit_dto);
  static ServiceResult removeByUnitId(const std::string& unit_id);
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getAll();
};
