#include <controller/goods/goods_price_controller.h>
#include <service/goods/goods_price_service.h>

void GoodsPriceController::registerRoutes(crow::SimpleApp &app) {
  CROW_ROUTE(app, "/api/goods_price/add")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsPriceService::create(req.body);
      });

  CROW_ROUTE(app, "/api/goods_price/get_by_page")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsPriceService::getByPage(req.body);
      });

  CROW_ROUTE(app, "/api/goods_price/get_all").methods("GET"_method)([]() {
    return GoodsPriceService::getAll();
  });

  // 其他路由...
}
