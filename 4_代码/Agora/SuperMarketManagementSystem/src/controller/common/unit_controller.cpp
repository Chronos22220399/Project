#include <controller/common/unit_controller.h>
#include <service/common/unit_service.h>

void UnitController::registerRoutes(crow::SimpleApp& app)
{
  CROW_ROUTE(app, "/api/unit/create")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELD(j, "unit_id");
      CHECK_REQUIRED_FIELDS(j, UnitDTO::required_fields);

      auto unit_dto = UnitDTO::from_json(j);
      unit_dto.unit_id = utils::create_id("U-");

      auto res = UnitService::create(unit_dto);

      return utils::to_response(res, 201);
    });

  CROW_ROUTE(app, "/api/unit/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELDS(j, UnitDTO::required_fields);

      auto unit_dto = UnitDTO::from_json(j);
      auto unit_id = unit_dto.unit_id;

      auto res = UnitService::updateByUnitId(unit_id, unit_dto);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/unit/remove")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELD(j, "unit_id");
      auto unit_id = j.at("unit_id").get<ex_id_type>();

      auto res = UnitService::removeByUnitId(unit_id);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/unit/get_by_page")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELD(j, "page");
      CHECK_REQUIRED_FIELD(j, "page_size");

      int page = j.value("page", 1);
      int page_size = j.value("page_size", 10);

      auto res = UnitService::getByPage(page, page_size);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/unit/get_all").methods("GET"_method)([]() {
    auto res = UnitService::getAll();
    return utils::to_response(res, 200);
  });

  // 其他路由...
}


// 不做：系统管理模块（系统日志管理、数据备份与恢复、系统更新与维护）
// yk
//  商品管理模块全部、系统管理模块（用户权限管理、系统设置）、会员管理模块（员工信息录入）、
//  员工管理模块（员工信息录入）、仓库管理模块（仓库信息管理、商品入库管理、商品出库管理、库存报警管理）
//
// 剩余业务
// 销售管理模块（销售订单录入、销售退货管理、销售统计报表、商品销售排行榜）、
// 供应商管理模块（供应商信息录入 供应商合同管理、供应商评价管理、采购订单管理）
//
