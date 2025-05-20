#include <common/common_utils.hpp>
#include <common/uni_define.h>
// third_party
#include <fmt/format.h>
// serv
#include <service/goods/goods_price_service.h>
// repo
#include <repository/goods/goods_price_repository.h>
#include <repository/goods/goods_repository.h>


// Implemented
// MARK: 商品价格-创建服务
ServiceResult GoodsPriceService::create(const GoodsPriceDTO& gp_dto)
{
  if (gp_dto.goods_rk_id == 0) {
    return {false, "Goods not found."};
  }

  // 检查商品价格是否已存在，若存在则返回冲突错误
  if (GoodsPriceRepository::existsByGoodsRKId(gp_dto.goods_rk_id)) {
    return {false, "Goods price already exists. You can only "
                   "modify, delete, or query it."};
  }

  // 创建商品价格
  bool success = GoodsPriceRepository::create(gp_dto).has_value();

  if (!success)
    return {false, "Create goods price failed."};
  return {true};
}

// MARK: 商品价格-删除服务
ServiceResult GoodsPriceService::removeByGoodsId(const std::string& goods_id)
{
  auto& cache = GlobalIdCache::getInstance();
  auto goods_rk_id = cache.getInternalId("goods", goods_id);

  if (goods_rk_id == 0) {
    return {false, "Goods not found."};
  }

  // 检查是否存在与 goods_rk_id 对应的商品价格
  if (!GoodsPriceRepository::existsByGoodsRKId(goods_rk_id)) {
    return {false, "Goods price not found."};
  }

  // 删除商品价格
  bool success = GoodsPriceRepository::removeByGoodsRKId(goods_rk_id);

  if (!success) {
    return {false, "Remove goods price failed."};
  }
  return {true};
}

// MARK: 商品价格-更新服务
//
// @param body - 请求体（JSON字符串），包含 goods_id, price, start_time, note
// @return crow::response
//   成功: 200, 仅返回 code 字段
//   失败: 400, JSON解析或字段缺失
//         404, 商品不存在或商品价格不存在
//         500, 数据库更新异常
ServiceResult GoodsPriceService::updateByGoodsRKId(const in_id_type goods_rk_id,
                                                   const GoodsPriceDTO& gp_dto)
{
  if (goods_rk_id == 0) {
    return {false, "Goods not found."};
  }

  // 检查是否存在与 goods_rk_id 对应的商品价格
  if (!GoodsPriceRepository::existsByGoodsRKId(goods_rk_id)) {
    return {false, "Goods price not found."};
  }

  // 更新商品价格
  bool success = GoodsPriceRepository::updateByGoodsRKId(goods_rk_id, gp_dto);
  if (!success) {
    return {false, "Update goods price failed."};
  }
  return {true};
}

// MARK: 商品价格-分页查询服务
//
// @param body - 请求体（JSON字符串），可选包含 page, page_size 字段
// @return crow::response
//   成功: 200, JSON 包含分页后的商品价格信息（含success, total, page,
//   page_size, data） 失败: 400, 分页参数非法; 500, 数据库查询异常
ServiceResult GoodsPriceService::getByPage(const int page, const int page_size)
{
  // 校验分页参数有效性
  if (page < 1 || page_size < 1) {
    return {false, "Invalid page or page_size"};
  }

  auto offset = (page - 1) * page_size;

  // 获取商品价格总数
  count_type total = GoodsPriceRepository::count();
  auto goods_price_list = GoodsPriceRepository::getByPage(page_size, offset);

  nlohmann::json data{{"success", true},
                      {"total", total},
                      {"page", page},
                      {"page_size", page_size},
                      {"items", goods_price_list}};

  return {true, "", data};
}

// Not implemented !
ServiceResult GoodsPriceService::getAll()
{
  return {false, "Not implemented yet."};
}
