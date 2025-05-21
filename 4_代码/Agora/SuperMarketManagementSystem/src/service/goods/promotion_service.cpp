#include <common/common_utils.hpp>
#include <common/global_id_cache.hpp>
#include <fmt/format.h>
#include <repository/goods/promotion_repository.h>
#include <service/goods/promotion_service.h>


// MARK: 促销活动-创建服务
ServiceResult PromotionService::create(PromotionDTO& promotion_dto)
{
  // 检测类型是否合法
  if (!utils::in(promotion_dto.type, PromotionDTO::type_domain)) {
    return {false, "type must be 'discount' or 'full reduction'."};
  }
  // 检测状态是否合法
  if (!utils::in(promotion_dto.status, PromotionDTO::status_domain)) {
    return {false, "status must be 'active', 'expired', or 'draft'."};
  }

  promotion_dto.promotion_id = utils::create_id("P-");

  // 插入促销活动记录
  auto res = PromotionRepository::create(promotion_dto);
  if (!res) {
    return {false, "Create promotion failed"};
  }

  GlobalIdCache::getInstance().update("promotion", promotion_dto.promotion_id,
                                      res.value());
  return {true};
}

// MARK: 促销活动-删除服务
//
// @param body - 请求体（JSON字符串），包含 promotion_id
// @return ServiceResult
//   成功: 200, 仅返回 code 字段
//   失败: 400, JSON解析或字段缺失
//         500, 数据库删除异常
ServiceResult
PromotionService::removeByPromotionId(const std::string& promotion_id)
{
  auto& cache = GlobalIdCache::getInstance();
  auto id = cache.getInternalId("promotion", promotion_id);

  if (id == 0) {
    return {false, "Promotion not found."};
  }

  // 数据库删除促销活动
  bool success = PromotionRepository::removeByPromotionId(promotion_id);

  if (!success) {
    return {false, "Remove promotion failed"};
  }

  cache.invalidate("promotion", promotion_id);
  return {true};
}

// MARK: 促销活动-更新服务
//
// @param body - 请求体（JSON字符串），包含 promotion_id, name, description,
// type,
//               start_time, end_time, status
// @return ServiceResult
//   成功: 200, 仅返回 code 字段
//   失败: 400, JSON解析或字段缺失
//         404, 促销活动不存在
//         500, 数据库更新异常
ServiceResult
PromotionService::updateByPromotionId(const std::string& promotion_id,
                                      PromotionDTO& promotion_dto)
{
  // 校验类型是否合法
  if (!utils::in(promotion_dto.type, PromotionDTO::type_domain)) {
    return {false, "type must be 'discount' or 'full reduction'."};
  }
  // 校验状态是否合法
  if (!utils::in(promotion_dto.status, PromotionDTO::status_domain)) {
    return {false, "status must be 'active', 'expired', or 'draft'."};
  }

  // 数据库更新促销活动
  bool success = PromotionRepository::updateByPromotionId(
    promotion_dto.promotion_id, promotion_dto);

  if (!success) {
    return {false, "Update promotion failed."};
  }
  return {true};
}

// MARK: 促销活动-分页查询服务
//
// @param body - 请求体（JSON字符串），包含 page 和 page_size，默认值为 1 和
// 10
// @return ServiceResult
//   成功: 200, JSON 包含分页后的促销活动记录信息（含success, total, page,
//   page_size, data） 失败: 400, 分页参数非法; 500, 数据库查询异常
ServiceResult PromotionService::getByPage(const int page, const int page_size)
{
  // 校验分页参数有效性
  if (page <= 0 || page_size <= 0) {
    return {false, "Invalid page or page_size"};
  }

  auto offset = (page - 1) * page_size;

  // 获取促销活动总数
  count_type total = PromotionRepository::count();
  auto promotions = PromotionRepository::getByPage(page_size, offset);

  // 构造响应
  nlohmann::json data{{"success", true},
                      {"total", total},
                      {"page", page},
                      {"page_size", page_size},
                      {"items", promotions}};

  return {true, "", data};
}

// MARK: 促销活动-获取所有记录服务
//
// @return ServiceResult
//   成功: 200, JSON 包含所有促销活动记录信息（含success, total, data）
//   失败: 500, 数据库查询异常
ServiceResult PromotionService::getAll()
{
  // 获取所有促销活动记录
  auto promotions = PromotionRepository::getAll();

  // 构造响应
  nlohmann::json data{
    {"success", true}, {"total", promotions.size()}, {"items", promotions}};

  return {true, data};
}
