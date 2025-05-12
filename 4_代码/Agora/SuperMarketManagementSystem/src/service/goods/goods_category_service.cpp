#include <common/common_utils.hpp>
#include <common/global_id_cache.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/goods/goods_category_repository.h>
#include <service/goods/goods_category_service.h>

using json = nlohmann::json;

const std::vector<std::string> required_fields = {
    "goods_category_id", "goods_category_name", "goods_category_description",
    "parent_category_id"};

// MARK: 商品分类创建服务
//
// @param body - 请求体（JSON字符串），包含 category_name, category_description,
// parent_category_id
// @return crow::response
//   成功: 201, JSON 包含 goods_category_id 和 create_time
//   失败: 400, JSON解析或字段缺失; 500, 数据库错误
crow::response GoodsCategoryService::create(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j); // 检查并解析JSON，失败自动返回400

  CHECK_REQUIRED_FIELDS(j, required_fields); // 检查必填字段

  try {
    auto gc_dto = GoodsCategoryDTO::from_json(j);
    gc_dto.goods_category_id = utils::create_id("GC"); // 生成外部ID

    auto insert_res = GoodsCategoryRepository::create(gc_dto);
    if (insert_res) {
      json res = {{"code", 201},
                  {"data",
                   {{"goods_category_id", gc_dto.goods_category_id},
                    {"create_time", utils::get_current_iso8601()}}}};

      auto &cache = GlobalIdCache::getInstance();
      cache.update("goods_category", gc_dto.goods_category_id,
                   insert_res.value());

      return crow::response(201, res.dump());
    }

    return SET_ERR_RESPONSE(500, "DB_ERROR");

  } catch (const std::exception &e) {
    return SET_ERR_RESPONSE(500, e.what());
  }
}

// MARK: 商品分类-获取全部分类服务
//
// @return crow::response
//   成功: 200, JSON 包含全部分类信息（含success, total, data）
//   失败: 500, 数据库查询异常
crow::response GoodsCategoryService::getAll() {
  try {
    auto goods_category_list = GoodsCategoryRepository::getAll();

    nlohmann::json data = {"data",
                           {{"success", true},
                            {"total", goods_category_list.size()},
                            {"items", goods_category_list}}};

    return SET_SUC_DATA_RESPONSE(data);
  } catch (const std::exception &e) {
    return SET_ERR_RESPONSE(500, e.what());
  }
}

// MARK: 商品分类-分页查询服务
//
// @param body - 请求体（JSON字符串），可选包含 page, page_size 字段
// @return crow::response
//   成功: 200, JSON 包含分页后的分类信息（含success, total, page, page_size,
//   data） 失败: 400, 分页参数非法; 500, 数据库查询异常
crow::response GoodsCategoryService::getByPage(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  int page = j.value("page", 1);
  int page_size = j.value("page_size", 10);
  if (page <= 0 || page_size <= 0) {
    return SET_ERR_RESPONSE(400, "Invalid page or page_size");
  }

  auto offset = (page - 1) * page_size;

  try {
    count_type total = GoodsCategoryRepository::count();
    auto goods_category_list =
        GoodsCategoryRepository::getByPage(page_size, offset);

    nlohmann::json data = {"data",
                           {{"success", true},
                            {"total", total},
                            {"page", page},
                            {"page_size", page_size},
                            {"items", goods_category_list}}};

    return SET_SUC_DATA_RESPONSE(data);
  } catch (const std::exception &e) {
    return SET_ERR_RESPONSE(500, e.what());
  }
}

// MARK: 商品分类-删除服务
//
// @param body - 请求体（JSON字符串），包含 goods_category_id
// @return crow::response
//   成功: 200, 仅返回 code 字段
//   失败: 400, JSON解析或字段缺失
//         404, 分类不存在
//         500, 数据库删除异常
crow::response
GoodsCategoryService::removeByGoodsCategoryId(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  // 检查必填字段
  CHECK_REQUIRED_FIELD(j, "goods_category_id");
  auto goods_category_id = j.at("goods_category_id").get<ex_id_type>();

  auto &cache = GlobalIdCache::getInstance();
  auto id = cache.getInternalId("goods_category", goods_category_id);

  // 判断分类是否存在
  if (id == 0) {
    return SET_ERR_RESPONSE(404, "Goods category not found.");
  }

  // 删除分类
  bool success = GoodsCategoryRepository::removeById(id);
  if (success) {
    cache.invalidate("goods_catogory", goods_category_id);
    return SET_EMPTY_DATA_RESPONSE(200);
  }
  return SET_ERR_RESPONSE(500, "DB_DELETE_ERROR");
}

// MARK: 商品分类-更新服务
//
// @param body - 请求体（JSON字符串），包含 goods_category_id, category_name,
// category_description, parent_category_id
// @return crow::response
//   成功: 200, 仅返回 code 字段
//   失败: 400, JSON解析或字段缺失
//         404, 分类不存在
//         500, 数据库更新异常
crow::response
GoodsCategoryService::updateByGoodsCategoryId(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELDS(j, required_fields);
  CHECK_REQUIRED_FIELD(j, "goods_category_id");

  auto goods_category_id = j.at("goods_category_id").get<ex_id_type>();

  auto &cache = GlobalIdCache::getInstance();
  auto id = cache.getInternalId("goods_category", goods_category_id);

  if (id == 0) {
    return SET_ERR_RESPONSE(404, "Goods category not found.");
  }

  auto goods_category_dto = GoodsCategoryDTO::from_json(j);

  bool success = GoodsCategoryRepository::updateByGoodsCategoryId(
      goods_category_id, goods_category_dto);

  return success ? SET_EMPTY_DATA_RESPONSE(200)
                 : SET_ERR_RESPONSE(500, "DB_UPDATE_ERROR");
}

crow::response
GoodsCategoryService::getByGoodsCategoryId(const std::string &body) {
  return crow::response(501, "Not implemet yet.");
}
