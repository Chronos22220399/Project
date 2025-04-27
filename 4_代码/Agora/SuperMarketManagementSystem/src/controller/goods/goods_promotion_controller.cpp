#include <controller/goods/goods_promotion_controller.h>
#include <service/goods/goods_promotion_service.h>

void GoodsPromotionController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/goods_promotion/add")
        .methods("POST"_method)([](const crow::request& req) {
            return GoodsPromotionService::add(req.body);
        });
        
    CROW_ROUTE(app, "/api/goods_promotion/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            return GoodsPromotionService::getByPage(req.body);
        });
        
    CROW_ROUTE(app, "/api/goods_promotion/getAll")
        .methods("GET"_method)([]() {
            return GoodsPromotionService::getAll();
        });
        
    // 其他路由...
}
