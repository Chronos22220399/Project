#include <controller/goods/promotion_controller.h>
#include <service/goods/promotion_service.h>

void PromotionController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/promotion/add")
        .methods("POST"_method)([](const crow::request& req) {
            return PromotionService::add(req.body);
        });
        
    CROW_ROUTE(app, "/api/promotion/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            return PromotionService::getByPage(req.body);
        });
        
    CROW_ROUTE(app, "/api/promotion/getAll")
        .methods("GET"_method)([]() {
            return PromotionService::getAll();
        });
        
    // 其他路由...
}
