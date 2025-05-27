#include <controller/member/member_level_controller.h>
#include <service/member/member_level_service.h>

void MemberLevelController::registerRoutes(crow::SimpleApp& app)
{
  CROW_ROUTE(app, "/api/member_level/create")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, MemberLevelDTO::required_fields);

      auto member_level_dto = MemberLevelDTO::from_json(j);

      auto res = MemberLevelService::create(member_level_dto);
      return utils::to_response(res, 201);
    });

  CROW_ROUTE(app, "/api/member_level/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, MemberLevelDTO::required_fields);

      auto member_level_dto = MemberLevelDTO::from_json(j);

      auto res = MemberLevelService::updateByLevelId(member_level_dto.level_id,
                                                     member_level_dto);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/member_level/remove")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查必填字段
      CHECK_REQUIRED_FIELD(j, "level_id");

      auto member_level_id = j.at("level_id").get<ex_id_type>();

      auto res = MemberLevelService::removeByLevelId(member_level_id);

      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/member_level/getByPage")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELD(j, "page");
      CHECK_REQUIRED_FIELD(j, "page_size");

      int page = j.value("page", 1);
      int page_size = j.value("page_size", 10);

      auto res = MemberLevelService::getByPage(page, page_size);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/member_level/getAll").methods("GET"_method)([]() {
    auto res = MemberLevelService::getAll();
    return utils::to_response(res, 200);
  });

  // 其他路由...
}
