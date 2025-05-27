#include <controller/employee/position_controller.h>
#include <service/employee/position_service.h>

void PositionController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/position/create")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, PositionDTO::required_fields);
            
            auto position_dto = PositionDTO::from_json(j);
            
            auto res = PositionService::create(position_dto);
            return utils::to_response(res, 201);
        });
        
    CROW_ROUTE(app, "/api/position/update")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, PositionDTO::required_fields);
            
            auto position_dto = PositionDTO::from_json(j);
            auto position_id = position_dto.position_id;
            
            auto res = PositionService::updateByPositionId(position_id, position_dto);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/position/remove")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);
            // 检查必填字段
            CHECK_REQUIRED_FIELD(j, "position_id");
            
            auto position_id = j.at("position_id").get<ex_id_type>();
            
            auto res = PositionService::removeByPositionId(position_id);
            
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/position/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);

            CHECK_REQUIRED_FIELD(j, "page");
            CHECK_REQUIRED_FIELD(j, "page_size");

            int page = j.value("page", 1);
            int page_size = j.value("page_size", 10);

            auto res = PositionService::getByPage(page, page_size);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/position/getAll")
        .methods("GET"_method)([]() {
            auto res = PositionService::getAll();
            return utils::to_response(res, 200);
        });
        
    // 其他路由...
}
