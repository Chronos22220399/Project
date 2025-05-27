#include <controller/system/permission_controller.h>
#include <service/system/permission_service.h>

void PermissionController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/permission/create")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, PermissionDTO::required_fields);
            
            auto permission_dto = PermissionDTO::from_json(j);
            
            auto res = PermissionService::create(permission_dto);
            return utils::to_response(res, 201);
        });
        
    CROW_ROUTE(app, "/api/permission/update")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, PermissionDTO::required_fields);
            
            auto permission_dto = PermissionDTO::from_json(j);
            auto permission_id = permission_dto.permission_id;
            
            auto res = PermissionService::updateByPermissionId(permission_id, permission_dto);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/permission/remove")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);
            // 检查必填字段
            CHECK_REQUIRED_FIELD(j, "permission_id");
            
            auto permission_id = j.at("permission_id").get<ex_id_type>();
            
            auto res = PermissionService::removeByPermissionId(permission_id);
            
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/permission/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);

            CHECK_REQUIRED_FIELD(j, "page");
            CHECK_REQUIRED_FIELD(j, "page_size");

            int page = j.value("page", 1);
            int page_size = j.value("page_size", 10);

            auto res = PermissionService::getByPage(page, page_size);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/permission/getAll")
        .methods("GET"_method)([]() {
            auto res = PermissionService::getAll();
            return utils::to_response(res, 200);
        });
        
    // 其他路由...
}
