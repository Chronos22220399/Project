#include <controller/sales/sales_order_controller.h>
#include <service/sales/sales_order_service.h>

void SalesOrderController::registerRoutes(crow::SimpleApp& app)
{
  CROW_ROUTE(app, "/api/sales_order/create")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, SalesOrderDTO::required_fields);

      auto sales_order_dto = SalesOrderDTO::from_json(j);

      auto res = SalesOrderService::create(sales_order_dto);
      return utils::to_response(res, 201);
    });

  CROW_ROUTE(app, "/api/sales_order/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, SalesOrderDTO::required_fields);

      auto sales_order_dto = SalesOrderDTO::from_json(j);
      auto sales_order_id = sales_order_dto.order_id;

      auto res = SalesOrderService::updateBySalesOrderId(sales_order_id,
                                                         sales_order_dto);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/sales_order/remove")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查必填字段
      CHECK_REQUIRED_FIELD(j, "sales_order_id");

      auto sales_order_id = j.at("sales_order_id").get<ex_id_type>();

      auto res = SalesOrderService::removeBySalesOrderId(sales_order_id);

      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/sales_order/getByPage")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELD(j, "page");
      CHECK_REQUIRED_FIELD(j, "page_size");

      int page = j.value("page", 1);
      int page_size = j.value("page_size", 10);

      auto res = SalesOrderService::getByPage(page, page_size);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/sales_order/getAll").methods("GET"_method)([]() {
    auto res = SalesOrderService::getAll();
    return utils::to_response(res, 200);
  });

  // 其他路由...
}
