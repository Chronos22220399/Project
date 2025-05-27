#include <controller/member/points_policy_controller.h>
#include <service/member/points_policy_service.h>

void PointsPolicyController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/points_policy/create")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, PointsPolicyDTO::required_fields);
            
            auto points_policy_dto = PointsPolicyDTO::from_json(j);
            
            auto res = PointsPolicyService::create(points_policy_dto);
            return utils::to_response(res, 201);
        });
        
    CROW_ROUTE(app, "/api/points_policy/update")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, PointsPolicyDTO::required_fields);
            
            auto points_policy_dto = PointsPolicyDTO::from_json(j);
            auto points_policy_id = points_policy_dto.points_policy_id;
            
            auto res = PointsPolicyService::updateByPointsPolicyId(points_policy_id, points_policy_dto);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/points_policy/remove")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);
            // 检查必填字段
            CHECK_REQUIRED_FIELD(j, "points_policy_id");
            
            auto points_policy_id = j.at("points_policy_id").get<ex_id_type>();
            
            auto res = PointsPolicyService::removeByPointsPolicyId(points_policy_id);
            
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/points_policy/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);

            CHECK_REQUIRED_FIELD(j, "page");
            CHECK_REQUIRED_FIELD(j, "page_size");

            int page = j.value("page", 1);
            int page_size = j.value("page_size", 10);

            auto res = PointsPolicyService::getByPage(page, page_size);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/points_policy/getAll")
        .methods("GET"_method)([]() {
            auto res = PointsPolicyService::getAll();
            return utils::to_response(res, 200);
        });
        
    // 其他路由...
}
