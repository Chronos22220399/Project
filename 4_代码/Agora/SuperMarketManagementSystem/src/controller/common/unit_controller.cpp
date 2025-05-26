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
