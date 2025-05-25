#include <controller/warehouse/stock_out_controller.h>
#include <service/warehouse/stock_out_service.h>

void StockOutController::registerRoutes(crow::SimpleApp& app)
{
  CROW_ROUTE(app, "/api/stock_out/create")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, StockOutDTO::required_fields);

      auto stock_out_dto = StockOutDTO::from_json(j);

      auto res = StockOutService::create(stock_out_dto);
      return utils::to_response(res, 201);
    });

  CROW_ROUTE(app, "/api/stock_out/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, StockOutDTO::required_fields);

      auto stock_out_dto = StockOutDTO::from_json(j);
      auto stock_out_id = stock_out_dto.stock_out_id;

      auto res =
        StockOutService::updateByStockOutId(stock_out_id, stock_out_dto);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/stock_out/remove")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查必填字段
      CHECK_REQUIRED_FIELD(j, "stock_out_id");

      auto stock_out_id = j.at("stock_out_id").get<ex_id_type>();

      auto res = StockOutService::removeByStockOutId(stock_out_id);

      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/stock_out/getByPage")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELD(j, "page");
      CHECK_REQUIRED_FIELD(j, "page_size");

      int page = j.value("page", 1);
      int page_size = j.value("page_size", 10);

      auto res = StockOutService::getByPage(page, page_size);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/stock_out/getAll").methods("GET"_method)([]() {
    auto res = StockOutService::getAll();
    return utils::to_response(res, 200);
  });

  // 其他路由...
}
