#include <controller/member/points_exchange_record_controller.h>
#include <service/member/points_exchange_record_service.h>

void PointsExchangeRecordController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/points_exchange_record/create")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, PointsExchangeRecordDTO::required_fields);
            
            auto points_exchange_record_dto = PointsExchangeRecordDTO::from_json(j);
            
            auto res = PointsExchangeRecordService::create(points_exchange_record_dto);
            return utils::to_response(res, 201);
        });
        
    CROW_ROUTE(app, "/api/points_exchange_record/update")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, PointsExchangeRecordDTO::required_fields);
            
            auto points_exchange_record_dto = PointsExchangeRecordDTO::from_json(j);
            auto points_exchange_record_id = points_exchange_record_dto.points_exchange_record_id;
            
            auto res = PointsExchangeRecordService::updateByPointsExchangeRecordId(points_exchange_record_id, points_exchange_record_dto);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/points_exchange_record/remove")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);
            // 检查必填字段
            CHECK_REQUIRED_FIELD(j, "points_exchange_record_id");
            
            auto points_exchange_record_id = j.at("points_exchange_record_id").get<ex_id_type>();
            
            auto res = PointsExchangeRecordService::removeByPointsExchangeRecordId(points_exchange_record_id);
            
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/points_exchange_record/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);

            CHECK_REQUIRED_FIELD(j, "page");
            CHECK_REQUIRED_FIELD(j, "page_size");

            int page = j.value("page", 1);
            int page_size = j.value("page_size", 10);

            auto res = PointsExchangeRecordService::getByPage(page, page_size);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/points_exchange_record/getAll")
        .methods("GET"_method)([]() {
            auto res = PointsExchangeRecordService::getAll();
            return utils::to_response(res, 200);
        });
        
    // 其他路由...
}
