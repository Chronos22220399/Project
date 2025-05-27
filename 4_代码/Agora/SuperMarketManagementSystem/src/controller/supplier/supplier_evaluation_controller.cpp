#include <controller/supplier/supplier_evaluation_controller.h>
#include <service/supplier/supplier_evaluation_service.h>

void SupplierEvaluationController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/supplier_evaluation/create")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, SupplierEvaluationDTO::required_fields);
            
            auto supplier_evaluation_dto = SupplierEvaluationDTO::from_json(j);
            
            auto res = SupplierEvaluationService::create(supplier_evaluation_dto);
            return utils::to_response(res, 201);
        });
        
    CROW_ROUTE(app, "/api/supplier_evaluation/update")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, SupplierEvaluationDTO::required_fields);
            
            auto supplier_evaluation_dto = SupplierEvaluationDTO::from_json(j);
            auto supplier_evaluation_id = supplier_evaluation_dto.supplier_evaluation_id;
            
            auto res = SupplierEvaluationService::updateBySupplierEvaluationId(supplier_evaluation_id, supplier_evaluation_dto);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/supplier_evaluation/remove")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);
            // 检查必填字段
            CHECK_REQUIRED_FIELD(j, "supplier_evaluation_id");
            
            auto supplier_evaluation_id = j.at("supplier_evaluation_id").get<ex_id_type>();
            
            auto res = SupplierEvaluationService::removeBySupplierEvaluationId(supplier_evaluation_id);
            
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/supplier_evaluation/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);

            CHECK_REQUIRED_FIELD(j, "page");
            CHECK_REQUIRED_FIELD(j, "page_size");

            int page = j.value("page", 1);
            int page_size = j.value("page_size", 10);

            auto res = SupplierEvaluationService::getByPage(page, page_size);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/supplier_evaluation/getAll")
        .methods("GET"_method)([]() {
            auto res = SupplierEvaluationService::getAll();
            return utils::to_response(res, 200);
        });
        
    // 其他路由...
}
