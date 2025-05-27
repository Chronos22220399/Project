#include <controller/member/member_purchase_record_controller.h>
#include <service/member/member_purchase_record_service.h>

void MemberPurchaseRecordController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/member_purchase_record/create")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, MemberPurchaseRecordDTO::required_fields);
            
            auto member_purchase_record_dto = MemberPurchaseRecordDTO::from_json(j);
            
            auto res = MemberPurchaseRecordService::create(member_purchase_record_dto);
            return utils::to_response(res, 201);
        });
        
    CROW_ROUTE(app, "/api/member_purchase_record/update")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, MemberPurchaseRecordDTO::required_fields);
            
            auto member_purchase_record_dto = MemberPurchaseRecordDTO::from_json(j);
            auto member_purchase_record_id = member_purchase_record_dto.member_purchase_record_id;
            
            auto res = MemberPurchaseRecordService::updateByMemberPurchaseRecordId(member_purchase_record_id, member_purchase_record_dto);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/member_purchase_record/remove")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);
            // 检查必填字段
            CHECK_REQUIRED_FIELD(j, "member_purchase_record_id");
            
            auto member_purchase_record_id = j.at("member_purchase_record_id").get<ex_id_type>();
            
            auto res = MemberPurchaseRecordService::removeByMemberPurchaseRecordId(member_purchase_record_id);
            
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/member_purchase_record/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);

            CHECK_REQUIRED_FIELD(j, "page");
            CHECK_REQUIRED_FIELD(j, "page_size");

            int page = j.value("page", 1);
            int page_size = j.value("page_size", 10);

            auto res = MemberPurchaseRecordService::getByPage(page, page_size);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/member_purchase_record/getAll")
        .methods("GET"_method)([]() {
            auto res = MemberPurchaseRecordService::getAll();
            return utils::to_response(res, 200);
        });
        
    // 其他路由...
}
