#include <controller/goods/goods_promotion_controller.h>
#include <service/goods/goods_promotion_service.h>

void GoodsPromotionController::registerRoutes(crow::SimpleApp &app) {
  // Not implemented !
  CROW_ROUTE(app, "/api/goods_promotion/create")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsPromotionService::create(req.body);
      });

  // Not implemented !
  CROW_ROUTE(app, "/api/goods_promotion/get_by_page")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsPromotionService::getByPage(req.body);
      });

  // Not implemented !
  CROW_ROUTE(app, "/api/goods_promotion/get_all").methods("GET"_method)([]() {
    return GoodsPromotionService::getAll();
  });

  // 其他路由...
}
