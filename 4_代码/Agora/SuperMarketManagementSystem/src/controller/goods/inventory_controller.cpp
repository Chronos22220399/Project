#include <controller/goods/inventory_controller.h>
#include <service/goods/inventory_service.h>

void InventoryController::registerRoutes(crow::SimpleApp &app) {
  // MARK: create
  CROW_ROUTE(app, "/api/inventory/create")
      .methods("POST"_method)([](const crow::request &req) {
        return InventoryService::create(req.body);
      });

  // MARK: read
  CROW_ROUTE(app, "/api/inventory/get_by_page")
      .methods("POST"_method)([](const crow::request &req) {
        return InventoryService::getByPage(req.body);
      });

  CROW_ROUTE(app, "/api/inventory/get_all").methods("GET"_method)([]() {
    return InventoryService::getAll();
  });

  // MARK: update
  // update by goods_id
  CROW_ROUTE(app, "/api/inventory/update")
      .methods("POST"_method)([](const crow::request &req) {
        return InventoryService::update(req.body);
      });

  // 其他路由...
}
