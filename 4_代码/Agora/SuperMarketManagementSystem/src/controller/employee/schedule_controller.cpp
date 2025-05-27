#include <controller/employee/schedule_controller.h>
#include <service/employee/schedule_service.h>

void ScheduleController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/schedule/create")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, ScheduleDTO::required_fields);
            
            auto schedule_dto = ScheduleDTO::from_json(j);
            
            auto res = ScheduleService::create(schedule_dto);
            return utils::to_response(res, 201);
        });
        
    CROW_ROUTE(app, "/api/schedule/update")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, ScheduleDTO::required_fields);
            
            auto schedule_dto = ScheduleDTO::from_json(j);
            auto schedule_id = schedule_dto.schedule_id;
            
            auto res = ScheduleService::updateByScheduleId(schedule_id, schedule_dto);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/schedule/remove")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);
            // 检查必填字段
            CHECK_REQUIRED_FIELD(j, "schedule_id");
            
            auto schedule_id = j.at("schedule_id").get<ex_id_type>();
            
            auto res = ScheduleService::removeByScheduleId(schedule_id);
            
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/schedule/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);

            CHECK_REQUIRED_FIELD(j, "page");
            CHECK_REQUIRED_FIELD(j, "page_size");

            int page = j.value("page", 1);
            int page_size = j.value("page_size", 10);

            auto res = ScheduleService::getByPage(page, page_size);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/schedule/getAll")
        .methods("GET"_method)([]() {
            auto res = ScheduleService::getAll();
            return utils::to_response(res, 200);
        });
        
    // 其他路由...
}
