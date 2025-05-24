#include "model/dto/warehouse/inventory_check_order_dto.hpp"


#include <controller/goods/inventory_controller.h>
#include <service/goods/inventory_service.h>



void InventoryController::registerRoutes(crow::SimpleApp& app)
{
  CROW_ROUTE(app, "/api/inventory/create")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查必填字段
      CHECK_REQUIRED_FIELDS(j, InventoryDTO::required_fields);

      auto inventory_dto = InventoryDTO::from_json(j);

      auto res = InventoryService::create(inventory_dto);

      return utils::to_response(res, 201);
    });


  CROW_ROUTE(app, "/api/inventory/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查并获取必填字段
      CHECK_REQUIRED_FIELDS(j, InventoryDTO::required_fields);
      auto inventory_dto = InventoryDTO::from_json(j);
      auto goods_rk_id = inventory_dto.goods_rk_id;

      auto res = InventoryService::updateByGoodsId(goods_rk_id, inventory_dto);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/inventory/get_by_goods_id")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELD(j, "goods_id");
      auto goods_id = j.at("goods_id").get<ex_id_type>();

      auto res = InventoryService::getByGoodsId(goods_id);

      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/inventory/get_by_warehouse_id")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      utils::check_required_field(j, "warehouse_id");
      auto warehouse_id = j.at("warehouse_id").get<ex_id_type>();

      auto res = InventoryService::getByGoodsId(warehouse_id);

      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/inventory/get_by_page")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      // 解析分页参数并设置默认值
      int page = j.value("page", 1);
      int page_size = j.value("page_size", 10);

      auto res = InventoryService::getByPage(page, page_size);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/inventory/remove").methods("POST"_method)([](const crow::request& req) {
    nlohmann::json j;
    auto &body = req.body;
    CHECK_AND_GET_JSON(j);
    utils::check_required_field(j, "inventory_id");

    auto inventory_id = j.at("inventory_id").get<ex_id_type>();
    auto res = InventoryService::removeByInventoryId(inventory_id);

    return utils::to_response(res, 200);
  });

  // Not implement !
  CROW_ROUTE(app, "/api/inventory/get_all").methods("GET"_method)([]() {
    auto res = InventoryService::getAll();
    return crow::response(501, "Not implemented yet.");
  });

  // 其他路由...
}
