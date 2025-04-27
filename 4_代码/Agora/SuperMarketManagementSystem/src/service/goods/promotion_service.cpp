#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/goods/promotion_repository.h>
#include <service/goods/promotion_service.h>

using json = nlohmann::json;

// Implemented

// std::string promotion_id = "";
// std::string name = "";
// std::string description = "";
// std::string type = "";
// datetime_type start_time = {};
// datetime_type end_time = {};
// std::string status = "";

namespace detail {
const std::vector<std::string> required_fields = {
    "promotion_id", "name",     "description", "type",
    "start_time",   "end_time", "status"};

const std::vector<std::string> required_type = {"discount", "full reduction"};

const std::vector<std::string> required_status = {"active", "expired", "draft"};

} // namespace detail

crow::response PromotionService::add(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELDS(j, detail::required_fields)

  // 检测类型信息是否是 discount / full reduction
  auto type = j.at("type").get<std::string>();
  if (!utils::in(type, detail::required_type))
    return crow::response(
        404, "type must in the midst of discount or full reduction.");

  // 检测状态是否为 active / expired / draft
  auto status = j.at("status").get<std::string>();
  if (!utils::in(status, detail::required_status))
    return crow::response(
        404, "status must in the midst of active or expired or draft");

  auto promotion_dto = PromotionDTO::from_json(j);

  bool success = PromotionRepository::create(promotion_dto);
  return success ? crow::response(200) : crow::response(500);
}

// 删除时可以在 body 中指定 criteria: promotion_id, promotion_name 选择删除标准
crow::response PromotionService::remove(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELD(j, "criteria");

  auto criteria = j.at("criteria").get<std::string>();
  bool success;
  if (criteria == "promotion_id") {
    CHECK_REQUIRED_FIELD(j, "promotion_id");
    auto promotion_id = j.at("promotion_id").get<id_type>();
    // 无需检查
    success = PromotionRepository::remove(promotion_id);
  } else if (criteria == "promotion_name") {
    CHECK_REQUIRED_FIELD(j, "promotion_name");
    auto promotion_name = j.at("promotion_name").get<std::string>();
    success = PromotionRepository::_remove(db::promotion{}.promotion_name ==
                                           promotion_name);
  }
  return success ? crow::response(200) : crow::response(500);
}

// Not implemented
crow::response PromotionService::getByPage(const std::string &body) {
  return crow::response(501, "Not implemented yet.");
}

crow::response PromotionService::getAll() {
  return crow::response(501, "Not implemented yet.");
}
