#include <controller/system/system_update_log_controller.h>
#include <service/system/system_update_log_service.h>

void SystemUpdateLogController::registerRoutes(crow::SimpleApp& app)
{
  CROW_ROUTE(app, "/api/system_update_log/create")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, SystemUpdateLogDTO::required_fields);

      auto system_update_log_dto = SystemUpdateLogDTO::from_json(j);

      auto res = SystemUpdateLogService::create(system_update_log_dto);
      return utils::to_response(res, 201);
    });

  CROW_ROUTE(app, "/api/system_update_log/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      CHECK_REQUIRED_FIELDS(j, SystemUpdateLogDTO::required_fields);

      auto system_update_log_dto = SystemUpdateLogDTO::from_json(j);
      auto update_id = system_update_log_dto.update_id;

      auto res = SystemUpdateLogService::updateByUpdateId(
        update_id, system_update_log_dto);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/system_update_log/remove")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查必填字段
      CHECK_REQUIRED_FIELD(j, "system_update_log_id");

      auto system_update_log_id =
        j.at("system_update_log_id").get<ex_id_type>();

      auto res = SystemUpdateLogService::removeByUpdateId(system_update_log_id);

      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/system_update_log/getByPage")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELD(j, "page");
      CHECK_REQUIRED_FIELD(j, "page_size");

      int page = j.value("page", 1);
      int page_size = j.value("page_size", 10);

      auto res = SystemUpdateLogService::getByPage(page, page_size);
      return utils::to_response(res, 200);
    });

  CROW_ROUTE(app, "/api/system_update_log/getAll").methods("GET"_method)([]() {
    auto res = SystemUpdateLogService::getAll();
    return utils::to_response(res, 200);
  });

  // 其他路由...
}
