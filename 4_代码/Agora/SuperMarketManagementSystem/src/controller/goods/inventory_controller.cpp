#include <controller/goods/inventory_controller.h>
#include <service/goods/inventory_service.h>

void InventoryController::registerRoutes(crow::SimpleApp &app) {
  CROW_ROUTE(app, "/api/inventory/add")
      .methods("POST"_method)([](const crow::request &req) {
        return InventoryService::create(req.body);
      });

  CROW_ROUTE(app, "/api/inventory/get_by_page")
      .methods("POST"_method)([](const crow::request &req) {
        return InventoryService::getByPage(req.body);
      });

  CROW_ROUTE(app, "/api/inventory/get_all").methods("GET"_method)([]() {
    return InventoryService::getAll();
  });

  // 其他路由...
}
