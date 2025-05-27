#include <controller/member/member_controller.h>
#include <service/member/member_service.h>


void MemberController::registerRoutes(crow::SimpleApp& app)
{
  CROW_ROUTE(app, "/api/member/create")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, MemberDTO::required_fields);

      auto member_dto = MemberDTO::from_json(j);

      auto res = MemberService::create(member_dto);
      return utils::to_response(res, 201);
    });

  CROW_ROUTE(app, "/api/member/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, MemberDTO::required_fields);

      auto member_dto = MemberDTO::from_json(j);
      auto member_id = member_dto.member_id;

      auto res = MemberService::updateByMemberId(member_id, member_dto);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/member/remove")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查必填字段
      CHECK_REQUIRED_FIELD(j, "member_id");

      auto member_id = j.at("member_id").get<ex_id_type>();

      auto res = MemberService::removeByMemberId(member_id);

      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/member/getByPage")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELD(j, "page");
      CHECK_REQUIRED_FIELD(j, "page_size");

      int page = j.value("page", 1);
      int page_size = j.value("page_size", 10);

      auto res = MemberService::getByPage(page, page_size);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/member/getAll").methods("GET"_method)([]() {
    auto res = MemberService::getAll();
    return utils::to_response(res, 200);
  });

  // 其他路由...
}
