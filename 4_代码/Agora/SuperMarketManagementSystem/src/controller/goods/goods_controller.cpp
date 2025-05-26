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

      auto page = j.at("page").get<int>();
      auto page_size = j.at("page_size").get<int>();

      auto res = GoodsService::getByPage(page, page_size);

      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/goods/get_all")
    .methods("GET"_method)([](const crow::request& req) {
      auto res = GoodsService::getAll();
      return utils::to_response(res, 200);
    });

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
