#include <controller/goods/goods_controller.h>
#include <service/goods/goods_service.h>

void GoodsController::registerRoutes(crow::SimpleApp &app) {
  // add goods
  CROW_ROUTE(app, "/api/goods/add")
      .methods("POST"_method)(
          [](const crow::request &req) { return GoodsService::add(req.body); });

  // get goods
  CROW_ROUTE(app, "/api/goods/get_by_page")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsService::getByPage(req.body);
      });

  // get all goods
  CROW_ROUTE(app, "/api/goods/get_all")
      .methods("GET"_method)(
          [](const crow::request &req) { return GoodsService::getAll(); });

  CROW_ROUTE(app, "/api/goods/get_goods_detail_info_by_id")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsService::getGoodsDetailInfoById(req.body);
      });

  // other routes
}
