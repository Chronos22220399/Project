#include <controller/goods/goods_category_controller.h>
#include <service/goods/goods_category_service.h>

const std::vector<std::string> required_fields = {
  "goods_category_id", "goods_category_name", "goods_category_description"
  };

void GoodsCategoryController::registerRoutes(crow::SimpleApp& app)
{
  CROW_ROUTE(app, "/api/goods_category/create")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      // 检查并解析JSON，失败自动返回400
      CHECK_AND_GET_JSON(j);
      // 检查必填字段
      CHECK_REQUIRED_FIELDS(j, required_fields);
      auto gc_dto = GoodsCategoryDTO::from_json(j);
      gc_dto.goods_category_id = utils::create_id("GC-");  // 生成外部ID

      auto res = GoodsCategoryService::create(gc_dto);
      return utils::to_response(res, 201);
    });


  CROW_ROUTE(app, "/api/goods_category/get_all")
    .methods("GET"_method)([](const crow::request& req) {
      auto res = GoodsCategoryService::getAll();
      return utils::to_response(res, 200);
    });


  CROW_ROUTE(app, "/api/goods_category/remove")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查并获取必填字段
      CHECK_REQUIRED_FIELD(j, "goods_category_id");
      auto goods_category_id = j.at("goods_category_id").get<ex_id_type>();

      auto res = GoodsCategoryService::removeByGoodsCategoryId(goods_category_id);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/goods_category/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查并获取必填字段
      CHECK_REQUIRED_FIELDS(j, required_fields);
      CHECK_REQUIRED_FIELD(j, "goods_category_id");
      auto gc_dto = GoodsCategoryDTO::from_json(j);
      auto goods_category_id = gc_dto.goods_category_id;

      auto res = GoodsCategoryService::updateByGoodsCategoryId(
        goods_category_id, gc_dto);
      return utils::to_response(res, 200);
    });

  // other routes
}
