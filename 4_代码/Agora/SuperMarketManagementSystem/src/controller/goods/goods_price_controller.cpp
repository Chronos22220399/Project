#include <controller/goods/goods_price_controller.h>
#include <service/goods/goods_price_service.h>

void GoodsPriceController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/goods_price/add")
        .methods("POST"_method)([](const crow::request& req) {
            return GoodsPriceService::add(req.body);
        });
        
    CROW_ROUTE(app, "/api/goods_price/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            return GoodsPriceService::getByPage(req.body);
        });
        
    CROW_ROUTE(app, "/api/goods_price/getAll")
        .methods("GET"_method)([]() {
            return GoodsPriceService::getAll();
        });
        
    // 其他路由...
}
