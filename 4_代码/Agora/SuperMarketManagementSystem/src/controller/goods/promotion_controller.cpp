#include <controller/goods/promotion_controller.h>
#include <service/goods/promotion_service.h>

void PromotionController::registerRoutes(crow::SimpleApp &app) {
  // MARK: create
  CROW_ROUTE(app, "/api/promotion/create")
      .methods("POST"_method)([](const crow::request &req) {
        return PromotionService::create(req.body);
      });

  // MARK: read
  CROW_ROUTE(app, "/api/promotion/get_by_page")
      .methods("POST"_method)([](const crow::request &req) {
        return PromotionService::getByPage(req.body);
      });

  CROW_ROUTE(app, "/api/promotion/get_all").methods("GET"_method)([]() {
    return PromotionService::getAll();
  });

  // MARK: update
  // update by promotino_id
  CROW_ROUTE(app, "/api/promotion/update")
      .methods("POST"_method)([](const crow::request &req) {
        return PromotionService::updateByPromotionId(req.body);
      });

  // MARK: update
  // update by promotion_id
  CROW_ROUTE(app, "/api/promotion/remove")
      .methods("POST"_method)([](const crow::request &req) {
        return PromotionService::removeByPromotionId(req.body);
      });

  // 其他路由...
}
