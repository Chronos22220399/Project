#include <controller/system/user_controller.h>
#include <service/system/user_service.h>

void UserController::registerRoutes(crow::SimpleApp& app)
{
  // MARK: 获取验证码
  CROW_ROUTE(app, "/api/user/get_vcode")
    .methods("GET"_method)([](const crow::request& req) {
      auto phone = req.url_params.get("phone");
      if (!phone) {
        return crow::response(
          400,
          nlohmann::json{{"code", 400}, {"error", "Missing phone parameter"}}
            .dump());
      }
      auto res = UserService::getVCode(phone);
      return utils::to_response(res, 200);
    });

  // MARK: 注册
  CROW_ROUTE(app, "/api/user/register")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, UserDTO::required_fields);
      CHECK_REQUIRED_FIELD(j, "vcode");

      auto user_dto = UserDTO::from_json(j);
      auto vcode = j.at("vcode").get<std::string>();

      auto res = UserService::regist(vcode, user_dto);
      return utils::to_response(res, 201);
    });

  // MARK: 登陆
  CROW_ROUTE(app, "/api/user/login")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELD(j, "username");
      CHECK_REQUIRED_FIELD(j, "password");

      auto username = j.at("username").get<std::string>();
      auto password = j.at("password").get<std::string>();

      auto res = UserService::login(username, password);
      return utils::to_response(res, 200);
    });
  CROW_ROUTE(app, "/api/user/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, UserDTO::required_fields);
      CHECK_REQUIRED_FIELD(j, "change_password");

      auto user_dto = UserDTO::from_json(j);
      auto user_id = user_dto.user_id;
      auto change_password = j.at("change_password").get<bool>();

      auto res =
        UserService::updateByUserId(user_id, change_password, user_dto);
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
