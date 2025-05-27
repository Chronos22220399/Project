#include <controller/employee/attendance_record_controller.h>
#include <service/employee/attendance_record_service.h>

void AttendanceRecordController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/attendance_record/create")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, AttendanceRecordDTO::required_fields);
            
            auto attendance_record_dto = AttendanceRecordDTO::from_json(j);
            
            auto res = AttendanceRecordService::create(attendance_record_dto);
            return utils::to_response(res, 201);
        });
        
    CROW_ROUTE(app, "/api/attendance_record/update")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, AttendanceRecordDTO::required_fields);
            
            auto attendance_record_dto = AttendanceRecordDTO::from_json(j);
            auto attendance_record_id = attendance_record_dto.attendance_record_id;
            
            auto res = AttendanceRecordService::updateByAttendanceRecordId(attendance_record_id, attendance_record_dto);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/attendance_record/remove")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);
            // 检查必填字段
            CHECK_REQUIRED_FIELD(j, "attendance_record_id");
            
            auto attendance_record_id = j.at("attendance_record_id").get<ex_id_type>();
            
            auto res = AttendanceRecordService::removeByAttendanceRecordId(attendance_record_id);
            
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/attendance_record/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);

            CHECK_REQUIRED_FIELD(j, "page");
            CHECK_REQUIRED_FIELD(j, "page_size");

            int page = j.value("page", 1);
            int page_size = j.value("page_size", 10);

            auto res = AttendanceRecordService::getByPage(page, page_size);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/attendance_record/getAll")
        .methods("GET"_method)([]() {
            auto res = AttendanceRecordService::getAll();
            return utils::to_response(res, 200);
        });
        
    // 其他路由...
}
