#include <controller/warehouse/warehouse_controller.h>
#include <service/warehouse/warehouse_service.h>

void WarehouseController::registerRoutes(crow::SimpleApp &app) {
  CROW_ROUTE(app, "/api/warehouse/add")
      .methods("POST"_method)([](const crow::request &req) {
        return WarehouseService::add(req.body);
      });

  CROW_ROUTE(app, "/api/warehouse/get_by_page")
      .methods("POST"_method)([](const crow::request &req) {
        return WarehouseService::getByPage(req.body);
      });

  CROW_ROUTE(app, "/api/warehouse/get_all").methods("GET"_method)([]() {
    return WarehouseService::getAll();
  });

  // 其他路由...
}
