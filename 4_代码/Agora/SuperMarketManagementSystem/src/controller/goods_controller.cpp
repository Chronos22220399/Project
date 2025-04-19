#include <controller/goods_controller.h>
#include <service/goods_service.h>

void GoodsController::registerRoutes(crow::SimpleApp &app) {
  CROW_ROUTE(app, "/goods/add")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsService::addGoods(req.body);
      });

  // other routes
}
