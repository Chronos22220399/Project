#include <controller/goods/promotion_controller.h>
#include <service/goods/promotion_service.h>

void PromotionController::registerRoutes(crow::SimpleApp &app) {
  CROW_ROUTE(app, "/api/promotion/add")
      .methods("POST"_method)([](const crow::request &req) {
        return PromotionService::create(req.body);
      });

  CROW_ROUTE(app, "/api/promotion/get_by_page")
      .methods("POST"_method)([](const crow::request &req) {
        return PromotionService::getByPage(req.body);
      });

  CROW_ROUTE(app, "/api/promotion/get_all").methods("GET"_method)([]() {
    return PromotionService::getAll();
  });

  // 其他路由...
}
