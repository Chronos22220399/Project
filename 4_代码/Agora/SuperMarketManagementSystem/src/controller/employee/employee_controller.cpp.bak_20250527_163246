#include <controller/employee/employee_controller.h>
#include <service/employee/employee_service.h>

void EmployeeController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/employee/create")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, EmployeeDTO::required_fields);
            
            auto employee_dto = EmployeeDTO::from_json(j);
            
            auto res = EmployeeService::create(employee_dto);
            return utils::to_response(res, 201);
        });
        
    CROW_ROUTE(app, "/api/employee/update")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, EmployeeDTO::required_fields);
            
            auto employee_dto = EmployeeDTO::from_json(j);
            auto employee_id = employee_dto.employee_id;
            
            auto res = EmployeeService::updateByEmployeeId(employee_id, employee_dto);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/employee/remove")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);
            // 检查必填字段
            CHECK_REQUIRED_FIELD(j, "employee_id");
            
            auto employee_id = j.at("employee_id").get<ex_id_type>();
            
            auto res = EmployeeService::removeByEmployeeId(employee_id);
            
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/employee/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);

            CHECK_REQUIRED_FIELD(j, "page");
            CHECK_REQUIRED_FIELD(j, "page_size");

            int page = j.value("page", 1);
            int page_size = j.value("page_size", 10);

            auto res = EmployeeService::getByPage(page, page_size);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/employee/getAll")
        .methods("GET"_method)([]() {
            auto res = EmployeeService::getAll();
            return utils::to_response(res, 200);
        });
        
    // 其他路由...
}
