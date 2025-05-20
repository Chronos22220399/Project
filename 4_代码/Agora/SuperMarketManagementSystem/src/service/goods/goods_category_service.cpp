#include <common/global_id_cache.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <service/goods/goods_category_service.h>

using json = nlohmann::json;


// MARK: 商品分类创建服务
//
// @param body - 请求体（JSON字符串），包含 category_name, category_description,
// parent_category_id
// @return crow::response
//   成功: 201, JSON 包含 goods_category_id 和 create_time
//   失败: 400, JSON解析或字段缺失; 500, 数据库错误
ServiceResult GoodsCategoryService::create(const GoodsCategoryDTO& gc_dto)
{

  auto insert_res = GoodsCategoryRepository::create(gc_dto);
  if (!insert_res)
    return {false, "插入商品分类时出现数据库错误"};

  auto& cache = GlobalIdCache::getInstance();
  cache.update("goods_category", gc_dto.goods_category_id, insert_res.value());

  nlohmann::json data{{"goods_category_id", gc_dto.goods_category_id},
                      {"create_time", utils::get_current_iso8601()}};

  return {true, "", data};
}


// MARK: 商品分类-获取全部分类服务
//
// @return crow::response
//   成功: 200, JSON 包含全部分类信息（含success, total, data）
//   失败: 500, 数据库查询异常
ServiceResult GoodsCategoryService::getAll()
{
  auto goods_category_list = GoodsCategoryRepository::getAll();

  nlohmann::json data = {{"success", true},
                         {"total", goods_category_list.size()},
                         {"items", goods_category_list}};

  return {true, "", data};
}

// MARK: 商品分类-分页查询服务
//
// @param body - 请求体（JSON字符串），可选包含 page, page_size 字段
// @return crow::response
//   成功: 200, JSON 包含分页后的分类信息（含success, total, page, page_size,
//   data） 失败: 400, 分页参数非法; 500, 数据库查询异常
ServiceResult GoodsCategoryService::getByPage(const int page,
                                              const int page_size)
{

  auto offset = (page - 1) * page_size;
  count_type total = GoodsCategoryRepository::count();
  auto goods_category_list =
    GoodsCategoryRepository::getByPage(page_size, offset);

  nlohmann::json data = {{"success", true},
                         {"total", total},
                         {"page", page},
                         {"page_size", page_size},
                         {"items", goods_category_list}};

  return {true, "", data};
}

// MARK: 商品分类-删除服务
//
// @param body - 请求体（JSON字符串），包含 goods_category_id
// @return crow::response
//   成功: 200, 仅返回 code 字段
//   失败: 400, JSON解析或字段缺失
//         404, 分类不存在
//         500, 数据库删除异常
ServiceResult GoodsCategoryService::removeByGoodsCategoryId(
  const std::string& goods_category_id)
{

  auto& cache = GlobalIdCache::getInstance();
  auto id = cache.getInternalId("goods_category", goods_category_id);

  // 判断分类是否存在
  if (id == 0) {
    return {false, "Goods category not found.", {}};
  }

  // 删除分类
  bool success = GoodsCategoryRepository::removeById(id);

  if (success) {
    cache.invalidate("goods_catogory", goods_category_id);
    return {true, "", {}};
  }
  return {false, "删除商品分类时失败", {}};
}

// MARK: 商品分类-更新服务
ServiceResult GoodsCategoryService::updateByGoodsCategoryId(
  const std::string& goods_category_id, const GoodsCategoryDTO& gc_dto)
{
  auto& cache = GlobalIdCache::getInstance();
  auto id = cache.getInternalId("goods_category", goods_category_id);

  if (id == 0) {
    return {false, "Can't find goods category", {}};
  }

  bool success =
    GoodsCategoryRepository::updateByGoodsCategoryId(goods_category_id, gc_dto);

  if (!success) {
    return {false, "Update goods category failed"};
  }
  return {true, "", {}};
}

ServiceResult
GoodsCategoryService::getByGoodsCategoryId(const std::string& body)
{
  return {false, "Not implemet yet.", {}};
}
