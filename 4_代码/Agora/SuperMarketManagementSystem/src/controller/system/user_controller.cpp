#include <controller/system/user_controller.h>
#include <service/system/user_service.h>

void UserController::registerRoutes(crow::SimpleApp& app)
{
  CROW_ROUTE(app, "/api/user/create")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, UserDTO::required_fields);

      auto user_dto = UserDTO::from_json(j);

      auto res = UserService::create(user_dto);
      return utils::to_response(res, 201);
    });

  CROW_ROUTE(app, "/api/user/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, UserDTO::required_fields);

      auto user_dto = UserDTO::from_json(j);
      auto user_id = user_dto.user_id;

      auto res = UserService::updateByUserId(user_id, user_dto);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/user/remove")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查必填字段
      CHECK_REQUIRED_FIELD(j, "user_id");

      auto user_id = j.at("user_id").get<ex_id_type>();

      auto res = UserService::removeByUserId(user_id);

      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/user/getByPage")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELD(j, "page");
      CHECK_REQUIRED_FIELD(j, "page_size");

      int page = j.value("page", 1);
      int page_size = j.value("page_size", 10);

      auto res = UserService::getByPage(page, page_size);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/user/getAll").methods("GET"_method)([]() {
    auto res = UserService::getAll();
    return utils::to_response(res, 200);
  });

  // 其他路由...
}
