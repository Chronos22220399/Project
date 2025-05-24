#include <controller/goods/goods_price_controller.h>
#include <nlohmann/json.hpp>
#include <service/goods/goods_price_service.h>

const std::vector<std::string> required_fields = {"goods_id", "price",
                                                  "start_time", "note"};

void GoodsPriceController::registerRoutes(crow::SimpleApp& app)
{
  CROW_ROUTE(app, "/api/goods_price/create")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELDS(j, required_fields);

      auto goods_price_dto = GoodsPriceDTO::from_json(j);
      auto res = GoodsPriceService::create(goods_price_dto);

      return utils::to_response(res, 201);
    });


  CROW_ROUTE(app, "/api/goods_price/remove")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查必填字段
      CHECK_REQUIRED_FIELD(j, "goods_id");
      auto goods_id = j.at("goods_id").get<ex_id_type>();

      auto res = GoodsPriceService::removeByGoodsId(goods_id);
      return utils::to_response(res, 200);
    });


  CROW_ROUTE(app, "/api/goods_price/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查必填字段
      CHECK_REQUIRED_FIELDS(j, required_fields);

      auto goods_price_dto = GoodsPriceDTO::from_json(j);
      auto res = GoodsPriceService::updateByGoodsRKId(
        goods_price_dto.goods_rk_id, goods_price_dto);

      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/goods_price/get_by_page")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      // 解析分页参数并设置默认值
      int page = j.value("page", 1);
      int page_size = j.value("page_size", 10);

      auto res = GoodsPriceService::getByPage(page, page_size);
      return utils::to_response(res, 200);
    });

  // Not implemented !
  CROW_ROUTE(app, "/api/goods_price/get_all").methods("GET"_method)([]() {
    auto res = GoodsPriceService::getAll();
    return crow::response(501, "Not implemented yet.");
  });

  // 其他路由...
}
