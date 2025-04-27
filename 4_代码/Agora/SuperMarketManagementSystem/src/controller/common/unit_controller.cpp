#include <controller/common/unit_controller.h>
#include <service/common/unit_service.h>

void UnitController::registerRoutes(crow::SimpleApp &app) {
  CROW_ROUTE(app, "/api/unit/add")
      .methods("POST"_method)(
          [](const crow::request &req) { return UnitService::add(req.body); });

  CROW_ROUTE(app, "/api/unit/get_by_page")
      .methods("POST"_method)([](const crow::request &req) {
        return UnitService::getByPage(req.body);
      });

  CROW_ROUTE(app, "/api/unit/get_all").methods("GET"_method)([]() {
    return UnitService::getAll();
  });

  // 其他路由...
}
