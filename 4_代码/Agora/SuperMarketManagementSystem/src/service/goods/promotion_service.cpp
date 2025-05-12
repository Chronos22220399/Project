#include <common/common_utils.hpp>
#include <common/global_id_cache.hpp>
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

// MARK: 促销活动-创建服务
//
// @param body - 请求体（JSON字符串），包含 promotion_id, name, description,
// type,
//               start_time, end_time, status
// @return crow::response
//   成功: 201, 仅返回 code 字段
//   失败: 400, JSON解析或字段缺失
//         404, 类型或状态非法
//         500, 数据库插入异常
crow::response PromotionService::create(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  // 检查必填字段
  CHECK_REQUIRED_FIELDS(j, detail::required_fields);

  // 检测类型是否合法
  auto type = j.at("type").get<std::string>();
  if (!utils::in(type, detail::required_type)) {
    return SET_ERR_RESPONSE(404,
                            "type must be 'discount' or 'full reduction'.");
  }

  // 检测状态是否合法
  auto status = j.at("status").get<std::string>();
  if (!utils::in(status, detail::required_status)) {
    return SET_ERR_RESPONSE(404,
                            "status must be 'active', 'expired', or 'draft'.");
  }

  auto promotion_dto = PromotionDTO::from_json(j);
  promotion_dto.promotion_id = utils::create_id("P-");

  // 插入促销活动记录
  auto res = PromotionRepository::create(promotion_dto);
  if (res) {
    auto &cache = GlobalIdCache::getInstance();
    cache.update("promotion", promotion_dto.promotion_id, res.value());
    return SET_EMPTY_DATA_RESPONSE(201);
  }
  return SET_ERR_RESPONSE(500, "DB_INSERT_ERROR");
}

// MARK: 促销活动-删除服务
//
// @param body - 请求体（JSON字符串），包含 promotion_id
// @return crow::response
//   成功: 200, 仅返回 code 字段
//   失败: 400, JSON解析或字段缺失
//         500, 数据库删除异常
crow::response PromotionService::removeByPromotionId(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  // 检查必填字段
  CHECK_REQUIRED_FIELD(j, "promotion_id");
  auto promotion_id = j.at("promotion_id").get<ex_id_type>();

  auto &cache = GlobalIdCache::getInstance();
  auto id = cache.getInternalId("promotion", promotion_id);

  if (id == 0) {
    return SET_ERR_RESPONSE(404, "Promotion not found.");
  }

  // 数据库删除促销活动
  bool success = PromotionRepository::removeByPromotionId(promotion_id);

  if (success) {
    cache.invalidate("promotion", promotion_id);
    return SET_EMPTY_DATA_RESPONSE(200);
  }

  return SET_ERR_RESPONSE(500, "DB_DELETE_ERROR");
}

// MARK: 促销活动-更新服务
//
// @param body - 请求体（JSON字符串），包含 promotion_id, name, description,
// type,
//               start_time, end_time, status
// @return crow::response
//   成功: 200, 仅返回 code 字段
//   失败: 400, JSON解析或字段缺失
//         404, 促销活动不存在
//         500, 数据库更新异常
crow::response PromotionService::updateByPromotionId(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  // 检查必填字段
  CHECK_REQUIRED_FIELDS(j, detail::required_fields);

  // 校验类型是否合法
  auto type = j.at("type").get<std::string>();
  if (!utils::in(type, detail::required_type)) {
    return SET_ERR_RESPONSE(404,
                            "type must be 'discount' or 'full reduction'.");
  }

  // 校验状态是否合法
  auto status = j.at("status").get<std::string>();
  if (!utils::in(status, detail::required_status)) {
    return SET_ERR_RESPONSE(404,
                            "status must be 'active', 'expired', or 'draft'.");
  }

  auto promotion = PromotionDTO::from_json(j);

  // 数据库更新促销活动
  bool success = PromotionRepository::updateByPromotionId(
      promotion.promotion_id, promotion);

  return success ? SET_EMPTY_DATA_RESPONSE(200)
                 : SET_ERR_RESPONSE(500, "DB_UPDATE_ERROR");
}

// MARK: 促销活动-分页查询服务
//
// @param body - 请求体（JSON字符串），包含 page 和 page_size，默认值为 1 和 10
// @return crow::response
//   成功: 200, JSON 包含分页后的促销活动记录信息（含success, total, page,
//   page_size, data） 失败: 400, 分页参数非法; 500, 数据库查询异常
crow::response PromotionService::getByPage(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  // 获取分页参数并设置默认值
  int page = j.value("page", 1);
  int page_size = j.value("page_size", 10);

  // 校验分页参数有效性
  if (page <= 0 || page_size <= 0) {
    return SET_ERR_RESPONSE(400, "Invalid page or page_size");
  }

  auto offset = (page - 1) * page_size;

  try {
    // 获取促销活动总数
    count_type total = PromotionRepository::count();
    auto promotions = PromotionRepository::getByPage(page_size, offset);

    // 构造响应
    nlohmann::json data{{"success", true},
                        {"total", total},
                        {"page", page},
                        {"page_size", page_size},
                        {"items", promotions}};

    return SET_SUC_DATA_RESPONSE(data);
  } catch (const std::exception &e) {
    LOG("PromotionService error: {}", e.what());
    return SET_ERR_RESPONSE(500, e.what());
  }
}

// MARK: 促销活动-获取所有记录服务
//
// @return crow::response
//   成功: 200, JSON 包含所有促销活动记录信息（含success, total, data）
//   失败: 500, 数据库查询异常
crow::response PromotionService::getAll() {
  try {
    // 获取所有促销活动记录
    auto promotions = PromotionRepository::getAll();

    // 构造响应
    nlohmann::json data{
        {"success", true}, {"total", promotions.size()}, {"items", promotions}};

    return SET_SUC_DATA_RESPONSE(data);
  } catch (const std::exception &e) {
    LOG("PromotionService error: {}", e.what());
    return SET_ERR_RESPONSE(500, e.what());
  }
}
