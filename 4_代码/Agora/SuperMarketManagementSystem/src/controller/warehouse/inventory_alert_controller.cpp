#include <controller/warehouse/inventory_alert_controller.h>
#include <service/warehouse/inventory_alert_service.h>

void InventoryAlertController::registerRoutes(crow::SimpleApp &app) {
  CROW_ROUTE(app, "/api/inventory_alert/create")
      .methods("POST"_method)([](const crow::request &req) {
        return InventoryAlertService::create(req.body);
      });

  CROW_ROUTE(app, "/api/inventory_alert/update")
      .methods("POST"_method)([](const crow::request &req) {
        return InventoryAlertService::update(req.body);
      });

  CROW_ROUTE(app, "/api/inventory_alert/remove")
      .methods("POST"_method)([](const crow::request &req) {
        return InventoryAlertService::remove(req.body);
      });

  CROW_ROUTE(app, "/api/inventory_alert/getByPage")
      .methods("POST"_method)([](const crow::request &req) {
        return InventoryAlertService::getByPage(req.body);
      });

  CROW_ROUTE(app, "/api/inventory_alert/getAll").methods("GET"_method)([]() {
    return InventoryAlertService::getAll();
  });

  // 其他路由...
}
