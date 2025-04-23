#include <controller/supplier/supplier_controller.h>
#include <service/supplier/supplier_service.h>

void SupplierController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/supplier/add")
        .methods("POST"_method)([](const crow::request& req) {
            return SupplierService::add(req.body);
        });
        
    CROW_ROUTE(app, "/api/supplier/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            return SupplierService::getByPage(req.body);
        });
        
    CROW_ROUTE(app, "/api/supplier/getAll")
        .methods("GET"_method)([]() {
            return SupplierService::getAll();
        });
        
    // 其他路由...
}
