#include <controller/sales/sales_return_controller.h>
#include <service/sales/sales_return_service.h>

void SalesReturnController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/sales_return/create")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, SalesReturnDTO::required_fields);
            
            auto sales_return_dto = SalesReturnDTO::from_json(j);
            
            auto res = SalesReturnService::create(sales_return_dto);
            return utils::to_response(res, 201);
        });
        
    CROW_ROUTE(app, "/api/sales_return/update")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, SalesReturnDTO::required_fields);
            
            auto sales_return_dto = SalesReturnDTO::from_json(j);
            auto sales_return_id = sales_return_dto.sales_return_id;
            
            auto res = SalesReturnService::updateBySalesReturnId(sales_return_id, sales_return_dto);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/sales_return/remove")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);
            // 检查必填字段
            CHECK_REQUIRED_FIELD(j, "sales_return_id");
            
            auto sales_return_id = j.at("sales_return_id").get<ex_id_type>();
            
            auto res = SalesReturnService::removeBySalesReturnId(sales_return_id);
            
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/sales_return/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);

            CHECK_REQUIRED_FIELD(j, "page");
            CHECK_REQUIRED_FIELD(j, "page_size");

            int page = j.value("page", 1);
            int page_size = j.value("page_size", 10);

            auto res = SalesReturnService::getByPage(page, page_size);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/sales_return/getAll")
        .methods("GET"_method)([]() {
            auto res = SalesReturnService::getAll();
            return utils::to_response(res, 200);
        });
        
    // 其他路由...
}
