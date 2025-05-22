// controller
#include <controller/goods/goods_controller.h>
// serv
#include <service/goods/goods_service.h>
// model
#include <model/dto/goods/goods_dto.hpp>
// tools
#include <common/uni_define.h>

#include <common/common_utils.hpp>
// third_party
#include <nlohmann/json.hpp>



void GoodsController::registerRoutes(crow::SimpleApp& app)
{
  CROW_ROUTE(app, "/api/goods/create")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      // 检查并解析 JSON
      CHECK_AND_GET_JSON(j);
      // 检查所需字段
      CHECK_REQUIRED_FIELDS(j, GoodsDTO::required_fields);
      // 将 JSON 转换为 DTO
      auto goods_dto = GoodsDTO::from_json(j);

      auto result = GoodsService::create(goods_dto);

      return utils::to_response(result);
    });

  CROW_ROUTE(app, "/api/goods/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, GoodsDTO::required_fields);

      auto goods_dto = GoodsDTO::from_json(j);
      auto goods_id = goods_dto.goods_id;

      auto res = GoodsService::updateByGoodsId(goods_id, goods_dto);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/goods/remove")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;

      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELD(j, "goods_id");

      auto goods_id = j.at("goods_id").get<ex_id_type>();
      auto res = GoodsService::removeByGoodsId(goods_id);
      return utils::to_response(res, 200);
    });


  CROW_ROUTE(app, "/api/goods/get_by_page")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      // 检测并获取 body 内的元素
      CHECK_AND_GET_JSON(j);
      // 检测 page 和 page_size 是否存在
      CHECK_REQUIRED_FIELD(j, "page");
      CHECK_REQUIRED_FIELD(j, "page_size");

      int page = j.value("page", 1);
      int page_size = j.value("page_size", 10);

      auto res = GoodsService::getByPage(page, page_size);


      return utils::to_response(res, 200);
    });

  // MARK: 获取全部商品概要信息 - GET /api/goods/get_all
  //
  // 成功响应 (200):
  // {
  //   "code": 200,
  //   "data": [
  //     {
  //       "goods_id": "Gxxxx",
  //       "goods_name": "商品名称",
  //       "category_name": "分类名称",
  //       "stock": 100,
  //       "external_info": {
  //         "supplier_code": "SP-8848",
  //         "warehouse_code": "WH-SH01"
  //       }
  //     }
  //   ]
  // }
  //
  // 错误响应：
  // 500 - 数据库查询失败
  CROW_ROUTE(app, "/api/goods/get_all")
    .methods("GET"_method)([](const crow::request& req) {
      auto res = GoodsService::getAll();
      return utils::to_response(res, 200);
    });

  // MARK: 获取商品详细信息 - POST /api/goods/get_goods_detail_info
  //
  // 请求JSON：
  // {
  //   "goods_id": string  // 必填（商品外部ID）
  // }
  //
  // 成功响应 (200):
  // {
  //   "code": 200,
  //   "data": {
  //     "goods_id": "Gxxxx",
  //     "goods_name": "商品名称",
  //     "quantity": 1000,         // 库存总量
  //     "unit": "件",             // 计量单位
  //     "warehouse_name": "上海仓库",
  //     "location": "A区-12号货架",
  //     "shelf_life_days": 365    // 保质期天数
  //   }
  // }
  //
  // 错误响应：
  // 400 - 商品ID缺失或格式错误
  // 404 - 商品不存在
  // 500 - 数据库查询失败
  CROW_ROUTE(app, "/api/goods/get_goods_detail_info")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELD(j, "goods_id");

      // 获取 id
      auto goods_id = j.at("goods_id").get<std::string>();
      auto id = GlobalIdCache::getInstance().getInternalId("goods", goods_id);

      auto res = GoodsService::getGoodsDetailInfoById(id);

      return utils::to_response(res, 200);
    });

  // other routes
}
