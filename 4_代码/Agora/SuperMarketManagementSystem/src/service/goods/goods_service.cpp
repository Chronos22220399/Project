// tools
#include <common/common_utils.hpp>
#include <common/global_id_cache.hpp>
// repo
#include <repository/goods/goods_repository.h>
// service
#include <service/goods/goods_service.h>
// model
#include <model/dto/goods/goods_dto.hpp>
// third_party
#include <fmt/format.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// MARK: 商品-创建服务
ServiceResult GoodsService::create(GoodsDTO& goods_dto)
{
  // 生成外部 ID
  goods_dto.goods_id = utils::create_id("G-");
  // 插入记录到数据库
  auto insert_res = GoodsRepository::create(goods_dto);

  // 如果插入失败，返回 500 错误
  if (!insert_res.has_value())
    return {false, "Create goods failed", {}};

  // 更新全局 ID 缓存
  GlobalIdCache::getInstance().update("goods", goods_dto.goods_id,
                                      insert_res.value());

  // 构造成功响应
  return {true,
          "",
          {{"code", 201},
           {"data",
            {{"goods_id", goods_dto.goods_id},
             {"create_time", utils::get_current_iso8601()}}}}};
}

ServiceResult GoodsService::getByPage(const int page, const int page_size)
{
  if (page <= 0 || page_size <= 0) {
    return {false, "Invalid Json: missing page or page_size.", {}};
  }

  // 分页查询
  auto offset = (page - 1) * page_size;

  // 获取分页数据
  count_type total = GoodsRepository::count();
  auto goods_list = GoodsRepository::getByPage(page_size, offset);

  json data{
    {"total", total},
    {"current_page", page},
    {"page_size", page_size},
    {"total_pages",
     static_cast<int>(std::ceil(total / static_cast<double>(page_size)))},
    {"items", goods_list},  // 确保每个item中的id字段已转换为string类型
  };

  return {true, "", data};
}

// MARK: read
ServiceResult GoodsService::getAll()
{
  auto goods_list = GoodsRepository::getAll();
  json data{
    {"success", true}, {"total", goods_list.size()}, {"items", goods_list}};

  return {true, "", data};
}

ServiceResult GoodsService::updateByGoodsId(const std::string& goods_id, GoodsDTO& goods_dto){
  auto &cache = GlobalIdCache::getInstance();
  auto id = cache.getInternalId("goods", goods_id);

  if (id == 0) return {false, "No goods found", {}};

  auto success = GoodsRepository::updateByGoodsId(id, goods_dto);

  if (!success) return {false, "Update goods failed", {}};
  return {true, "", goods_dto};
}

ServiceResult GoodsService::removeByGoodsId(const std::string& goods_id){
  auto &cache = GlobalIdCache::getInstance();
  auto id = cache.getInternalId("goods", goods_id);

  if (id == 0) return {false, "No goods found", {}};

  auto success = GoodsRepository::removeById(id);
  if (!success) return {false, "Remove goods failed", {}};
  return {true};
}



// MARK: 商品详细信息查询接口 - POST /api/goods/get_goods_detail_info_by_id
ServiceResult GoodsService::getGoodsDetailInfoById(const in_id_type id)
{
  auto infos = GoodsRepository::getGoodsDetailInfoById(id);

  json data{{"success", true}, {"total", infos.size()}, {"items", infos}};

  return {true, "", data};
}
