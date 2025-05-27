#include <controller/system/system_setting_controller.h>
#include <service/system/system_setting_service.h>

void SystemSettingController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/system_setting/create")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, SystemSettingDTO::required_fields);
            
            auto system_setting_dto = SystemSettingDTO::from_json(j);
            
            auto res = SystemSettingService::create(system_setting_dto);
            return utils::to_response(res, 201);
        });
        
    CROW_ROUTE(app, "/api/system_setting/update")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, SystemSettingDTO::required_fields);
            
            auto system_setting_dto = SystemSettingDTO::from_json(j);
            auto system_setting_id = system_setting_dto.system_setting_id;
            
            auto res = SystemSettingService::updateBySystemSettingId(system_setting_id, system_setting_dto);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/system_setting/remove")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);
            // 检查必填字段
            CHECK_REQUIRED_FIELD(j, "system_setting_id");
            
            auto system_setting_id = j.at("system_setting_id").get<ex_id_type>();
            
            auto res = SystemSettingService::removeBySystemSettingId(system_setting_id);
            
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/system_setting/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);

            CHECK_REQUIRED_FIELD(j, "page");
            CHECK_REQUIRED_FIELD(j, "page_size");

            int page = j.value("page", 1);
            int page_size = j.value("page_size", 10);

            auto res = SystemSettingService::getByPage(page, page_size);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/system_setting/getAll")
        .methods("GET"_method)([]() {
            auto res = SystemSettingService::getAll();
            return utils::to_response(res, 200);
        });
        
    // 其他路由...
}
