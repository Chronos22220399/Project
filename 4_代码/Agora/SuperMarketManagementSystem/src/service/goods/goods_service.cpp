// tools
#include <common/common_utils.hpp>
#include <common/global_id_cache.hpp>
// repo
#include <repository/goods/goods_repository.h>
// service
#include <service/goods/goods_service.h>
// third_party
#include <fmt/format.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

const std::vector<std::string> required_fields = {
    "goods_name",      "category_id", "supplier_id", "unit_id",
    "shelf_life_days", "barcode",     "image_url",   "description"};

// MARK: 商品-创建服务
//
// @param body - 请求体（JSON字符串），包含 goods_name, category_id,
// supplier_id, unit_id, shelf_life_days, barcode, image_url, description
// @return crow::response
//   成功: 201, 返回 code 和新建商品的 goods_id、创建时间
//   失败: 400, JSON解析失败或字段缺失
//         500, 数据库插入异常
crow::response GoodsService::create(const std::string &body) {
  nlohmann::json j;

  // 检查并解析 JSON
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELDS(j, required_fields);

  try {
    // 将 JSON 转换为 DTO
    auto goods_dto = GoodsDTO::from_json(j);

    // 生成外部 ID
    goods_dto.goods_id = utils::create_id("G-");

    // 插入记录到数据库
    auto insert_res = GoodsRepository::create(goods_dto);

    // 如果插入失败，返回 500 错误
    if (!insert_res.has_value())
      return SET_ERR_RESPONSE(500, "DB_ERROR");

    // 更新全局 ID 缓存
    auto &cache = GlobalIdCache::getInstance();
    cache.update("goods", goods_dto.goods_id, insert_res.value());

    // 构造成功响应
    return crow::response(
        201, nlohmann::json{{"code", 201},
                            {"data",
                             {{"goods_id", goods_dto.goods_id},
                              {"create_time", utils::get_current_iso8601()}}}}
                 .dump());

  } catch (const std::exception &e) {
    // 捕获异常并返回 500 错误
    return SET_ERR_RESPONSE(500, e.what());
  }
}

crow::response GoodsService::getByPage(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELD(j, "page");
  CHECK_REQUIRED_FIELD(j, "page_size");

  int page = j.value("page", 1);
  int page_size = j.value("page_size", 10);
  if (page <= 0 || page_size <= 0) {
    return SET_ERR_RESPONSE(400, "Invalid page or page_size");
  }

  // 分页查询
  auto offset = (page - 1) * page_size;

  try {
    // 获取分页数据
    count_type total = GoodsRepository::count();
    auto goods_list = GoodsRepository::getByPage(page_size, offset);

    json data{
        {"total", total},
        {"current_page", page},
        {"page_size", page_size},
        {"total_pages",
         static_cast<int>(std::ceil(total / static_cast<double>(page_size)))},
        {"items", goods_list}, // 确保每个item中的id字段已转换为string类型
    };

    return SET_SUC_DATA_RESPONSE(data);

  } catch (const std::exception &e) {
    return SET_ERR_RESPONSE(500, e.what());
  }
}

// MARK: read
crow::response GoodsService::getAll() {
  auto goods_list = GoodsRepository::getAll();
  try {
    json data{
        {"success", true}, {"total", goods_list.size()}, {"items", goods_list}};

    return SET_SUC_DATA_RESPONSE(data);
  } catch (const std::exception &e) {
    return SET_ERR_RESPONSE(500, e.what());
  }
}

// MARK: 商品详细信息查询接口 - POST /api/goods/get_goods_detail_info_by_id
crow::response GoodsService::getGoodsDetailInfoById(const std::string &body) {
  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  CHECK_REQUIRED_FIELD(j, "goods_id");

  auto goods_id = j.at("goods_id").get<std::string>();

  auto infos = GoodsRepository::getGoodsDetailInfoByGoodsId(goods_id);

  try {
    json data{{"success", true}, {"total", infos.size()}, {"items", infos}};

    return SET_SUC_DATA_RESPONSE(data);

  } catch (const std::exception &e) {
    return SET_ERR_RESPONSE(500, e.what());
  }
}
