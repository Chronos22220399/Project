#include <controller/employee/payroll_record_controller.h>
#include <service/employee/payroll_record_service.h>

void PayrollRecordController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/payroll_record/create")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, PayrollRecordDTO::required_fields);
            
            auto payroll_record_dto = PayrollRecordDTO::from_json(j);
            
            auto res = PayrollRecordService::create(payroll_record_dto);
            return utils::to_response(res, 201);
        });
        
    CROW_ROUTE(app, "/api/payroll_record/update")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, PayrollRecordDTO::required_fields);
            
            auto payroll_record_dto = PayrollRecordDTO::from_json(j);
            auto payroll_record_id = payroll_record_dto.payroll_record_id;
            
            auto res = PayrollRecordService::updateByPayrollRecordId(payroll_record_id, payroll_record_dto);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/payroll_record/remove")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);
            // 检查必填字段
            CHECK_REQUIRED_FIELD(j, "payroll_record_id");
            
            auto payroll_record_id = j.at("payroll_record_id").get<ex_id_type>();
            
            auto res = PayrollRecordService::removeByPayrollRecordId(payroll_record_id);
            
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/payroll_record/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);

            CHECK_REQUIRED_FIELD(j, "page");
            CHECK_REQUIRED_FIELD(j, "page_size");

            int page = j.value("page", 1);
            int page_size = j.value("page_size", 10);

            auto res = PayrollRecordService::getByPage(page, page_size);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/payroll_record/getAll")
        .methods("GET"_method)([]() {
            auto res = PayrollRecordService::getAll();
            return utils::to_response(res, 200);
        });
        
    // 其他路由...
}
