#include <controller/system/role_controller.h>
#include <service/system/role_service.h>

void RoleController::registerRoutes(crow::SimpleApp& app)
{
  CROW_ROUTE(app, "/api/role/create")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, RoleDTO::required_fields);

      auto role_dto = RoleDTO::from_json(j);

      auto res = RoleService::create(role_dto);
      return utils::to_response(res, 201);
    });

  CROW_ROUTE(app, "/api/role/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, RoleDTO::required_fields);

      auto role_dto = RoleDTO::from_json(j);
      auto role_id = role_dto.role_id;

      auto res = RoleService::updateByRoleId(role_id, role_dto);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/role/remove")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查必填字段
      CHECK_REQUIRED_FIELD(j, "role_id");

      auto role_id = j.at("role_id").get<ex_id_type>();

      auto res = RoleService::removeByRoleId(role_id);

      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/role/getByPage")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELD(j, "page");
      CHECK_REQUIRED_FIELD(j, "page_size");

      int page = j.value("page", 1);
      int page_size = j.value("page_size", 10);

      auto res = RoleService::getByPage(page, page_size);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/role/getAll").methods("GET"_method)([]() {
    auto res = RoleService::getAll();
    return utils::to_response(res, 200);
  });

  // 其他路由...
}
