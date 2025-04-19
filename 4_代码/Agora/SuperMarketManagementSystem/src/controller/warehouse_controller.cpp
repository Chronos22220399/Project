#include <controller/warehouse_controller.h>

void WareHouseController::registerRoutes(crow::SimpleApp &app) {
  CROW_ROUTE(app, "/warehouse/add")
      .methods("POST"_method)(
          [](const crow::request &req) { return crow::response(200); });

  // other routes
}
