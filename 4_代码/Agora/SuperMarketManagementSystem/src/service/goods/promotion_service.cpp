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

// MARK: create
crow::response PromotionService::create(const std::string &body) {
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

// MARK: read
crow::response PromotionService::getByPage(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  int page = j.value("page", 1);
  int page_size = j.value("page_size", 10);
  if (page <= 0 || page_size <= 0) {
    return crow::response(400, "Invalid page or page_size");
  }

  auto offset = (page - 1) * page_size;

  try {
    count_type total = PromotionRepository::count();
    auto promotions = PromotionRepository::getByPage(page_size, offset);

    nlohmann::json res;
    res["success"] = true;
    res["total"] = total;
    res["page"] = page;
    res["page_size"] = page_size;
    res["data"] = promotions;

    return crow::response(200, res.dump());
  } catch (const std::exception &e) {
    LOG("PromotionService error: {}", e.what());
    return crow::response(500, fmt::format("Error: {}", e.what()));
  }
}

crow::response PromotionService::getAll() {
  try {
    auto promotions = PromotionRepository::getAll();

    nlohmann::json res;
    res["success"] = true;
    res["total"] = promotions.size();
    res["data"] = promotions;

    return crow::response(200, res.dump());
  } catch (const std::exception &e) {
    LOG("PromotionService error: {}", e.what());
    return crow::response(500, fmt::format("Error: {}", e.what()));
  }
}

// MARK: update
crow::response PromotionService::updateByPromotionId(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELDS(j, detail::required_fields);

  auto promotion = PromotionDTO::from_json(j);

  bool success = PromotionRepository::updateByPromotionId(
      promotion.promotion_id, promotion);

  return success ? crow::response(200) : crow::response(500);
}

// MARK: delete
crow::response PromotionService::removeByPromotionId(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELD(j, "promotion_id");

  auto promotion_id = j.at("promotion_id").get<std::string>();
  // 无需检查，删除失败返回 false
  bool success = PromotionRepository::removeByPromotionId(promotion_id);

  return success ? crow::response(200) : crow::response(500);
}
