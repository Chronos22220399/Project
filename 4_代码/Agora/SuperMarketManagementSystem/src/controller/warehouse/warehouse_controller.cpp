#include <common/include.h>
#include <controller/warehouse/warehouse_controller.h>
#include <service/warehouse/warehouse_service.h>

// MARK: 仓库创建接口 - POST /api/warehouse/create
void WarehouseController::registerRoutes(crow::SimpleApp& app)
{
  CROW_ROUTE(app, "/api/warehouse/create")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      // 检查并解析 JSON
      CHECK_AND_GET_JSON(j);
      // 检查所需字段
      CHECK_REQUIRED_FIELDS(j, WarehouseDTO::required_fields);

      auto warehouse_dto = WarehouseDTO::from_json(j);

      auto res = WarehouseService::create(warehouse_dto);
      return utils::to_response(res, 201);
    });

  // MARK: 仓库更新接口 - POST /api/warehouse/update
  CROW_ROUTE(app, "/api/warehouse/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查字段
      CHECK_REQUIRED_FIELDS(j, WarehouseDTO::required_fields);

      auto warehouse_dto = WarehouseDTO::from_json(j);
      auto warehouse_id = warehouse_dto.warehouse_id;

      auto res =
        WarehouseService::updateByWarehouseId(warehouse_id, warehouse_dto);

      return utils::to_response(res, 200);
    });

  // MARK: 仓库分页查询接口 - POST /api/warehouse/get_by_page
  CROW_ROUTE(app, "/api/warehouse/get_by_page")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELD(j, "page");
      CHECK_REQUIRED_FIELD(j, "page_size");

      int page = j.value("page", 1);
      int page_size = j.value("page_size", 10);

      auto res = WarehouseService::getByPage(page, page_size);
      return utils::to_response(res, 200);
    });

  // MARK: 仓库状态设置接口 - POST /api/warehouse/set_status
  CROW_ROUTE(app, "/api/warehouse/set_status")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELD(j, "warehouse_id");
      CHECK_REQUIRED_FIELD(j, "status");

      auto warehouse_id = j.at("warehouse_id").get<ex_id_type>();
      auto status = j.at("status").get<status_type>();

      auto res = WarehouseService::setStatus(warehouse_id, status);

      return utils::to_response(res, 200);
    });

  // 其他路由...
}
