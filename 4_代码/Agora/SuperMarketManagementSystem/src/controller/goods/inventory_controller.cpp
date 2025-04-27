#include <controller/goods/inventory_controller.h>
#include <service/goods/inventory_service.h>

void InventoryController::registerRoutes(crow::SimpleApp &app) {
  CROW_ROUTE(app, "/api/inventory/add")
      .methods("POST"_method)([](const crow::request &req) {
        return InventoryService::add(req.body);
      });

  CROW_ROUTE(app, "/api/inventory/get")
      .methods("POST"_method)([](const crow::request &req) {
        return InventoryService::getByPage(req.body);
      });

  CROW_ROUTE(app, "/api/inventory/get_all").methods("GET"_method)([]() {
    return InventoryService::getAll();
  });

  // 其他路由...
}
