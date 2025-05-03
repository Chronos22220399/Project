#include <controller/common/unit_controller.h>
#include <service/common/unit_service.h>

void UnitController::registerRoutes(crow::SimpleApp &app) {
  CROW_ROUTE(app, "/api/unit/create")
      .methods("POST"_method)([](const crow::request &req) {
        return UnitService::create(req.body);
      });

  CROW_ROUTE(app, "/api/unit/get_by_page")
      .methods("POST"_method)([](const crow::request &req) {
        return UnitService::getByPage(req.body);
      });

  CROW_ROUTE(app, "/api/unit/get_all").methods("GET"_method)([]() {
    return UnitService::getAll();
  });

  // 其他路由...
}
