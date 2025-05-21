#pragma once
#include <common/common_utils.hpp>
#include <crow.h>
#include <model/dto/goods/promotion_dto.hpp>
#include <nlohmann/json.hpp>
#include <string>

class PromotionService {
  public:
  // Implemented
  static ServiceResult create(PromotionDTO& promotion_dto);

  static ServiceResult removeByPromotionId(const std::string& promotion_id);

  static ServiceResult updateByPromotionId(const std::string& promotion_id,
                                           PromotionDTO& promotion_dto);

  static ServiceResult getByPage(const int page, const int page_size);
  // Not implemented
  static ServiceResult getAll();
};
