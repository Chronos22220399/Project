#include <controller/supplier/supplier_controller.h>
#include <service/supplier/supplier_service.h>

void SupplierController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/myvenv/create")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, SupplierDTO::required_fields);
            
            auto supplier_dto = SupplierDTO::from_json(j);
            
            auto res = SupplierService::create(supplier_dto);
            return utils::to_response(res, 201);
        });
        
    CROW_ROUTE(app, "/api/myvenv/update")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, SupplierDTO::required_fields);
            
            auto supplier_dto = SupplierDTO::from_json(j);
            auto supplier_id = supplier_dto.supplier_id;
            
            auto res = SupplierService::updateBySupplierId(supplier_id, supplier_dto);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/myvenv/remove")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);
            // 检查必填字段
            CHECK_REQUIRED_FIELD(j, "supplier_id");
            
            auto supplier_id = j.at("supplier_id").get<ex_id_type>();
            
            auto res = SupplierService::removeBySupplierId(supplier_id);
            
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/myvenv/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);

            CHECK_REQUIRED_FIELD(j, "page");
            CHECK_REQUIRED_FIELD(j, "page_size");

            int page = j.value("page", 1);
            int page_size = j.value("page_size", 10);

            auto res = SupplierService::getByPage(page, page_size);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/myvenv/getAll")
        .methods("GET"_method)([]() {
            auto res = SupplierService::getAll();
            return utils::to_response(res, 200);
        });
        
    // 其他路由...
}
