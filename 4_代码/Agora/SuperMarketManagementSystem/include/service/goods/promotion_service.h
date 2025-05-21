#pragma once
#include <common/common_utils.hpp>
#include <crow.h>
#include <model/dto/goods/promotion_dto.hpp>
#include <nlohmann/json.hpp>
#include <string>

inline const std::vector<std::string> required_fields = {
  "promotion_id", "name",     "description", "type",
  "start_time",   "end_time", "status"};

inline const std::vector<std::string> required_type = {"discount",
                                                       "full reduction"};

inline const std::vector<std::string> required_status = {"active", "expired",
                                                         "draft"};

class PromotionService {
  public:
  // Implemented
  static ServiceResult create(const PromotionDTO& promotion_dto);

  static ServiceResult removeByPromotionId(const std::string& promotion_id);

  static ServiceResult updateByPromotionId(const std::string& promotion_id,
                                           const PromotionDTO& promotion_dto);

  static ServiceResult getByPage(const int page, const int page_size);
  // Not implemented
  static ServiceResult getAll();
};
