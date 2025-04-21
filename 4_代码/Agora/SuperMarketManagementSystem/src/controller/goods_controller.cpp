#include <controller/goods_controller.h>
#include <service/goods_service.h>

void GoodsController::registerRoutes(crow::SimpleApp &app) {
  // add goods
  CROW_ROUTE(app, "/goods/add")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsService::addGoods(req.body);
      });

  // get goods
  CROW_ROUTE(app, "/goods/get")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsService::getGoodsByPage(req.body);
      });

  // get all goods
  CROW_ROUTE(app, "/goods/get_all")
      .methods("GET"_method)(
          [](const crow::request &req) { return GoodsService::getAllGoods(); });
  // other routes
}
