#include <controller/warehouse/stock_in_controller.h>
#include <service/warehouse/stock_in_service.h>

void StockInController::registerRoutes(crow::SimpleApp& app)
{
  CROW_ROUTE(app, "/api/stock_in/create")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, StockInDTO::required_fields);

      auto stock_in_dto = StockInDTO::from_json(j);

      auto res = StockInService::create(stock_in_dto);
      return utils::to_response(res, 201);
    });

  CROW_ROUTE(app, "/api/stock_in/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, StockInDTO::required_fields);

      auto stock_in_dto = StockInDTO::from_json(j);
      auto stock_in_id = stock_in_dto.stock_in_id;

      auto res = StockInService::updateByStockInId(stock_in_id, stock_in_dto);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/stock_in/remove")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查必填字段
      CHECK_REQUIRED_FIELD(j, "stock_in_id");

      auto stock_in_id = j.at("stock_in_id").get<ex_id_type>();

      auto res = StockInService::removeByStockInId(stock_in_id);

      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/stock_in/getByPage")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELD(j, "page");
      CHECK_REQUIRED_FIELD(j, "page_size");

      int page = j.value("page", 1);
      int page_size = j.value("page_size", 10);

      auto res = StockInService::getByPage(page, page_size);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/stock_in/getAll").methods("GET"_method)([]() {
    auto res = StockInService::getAll();
    return utils::to_response(res, 200);
  });

  // 其他路由...
}
