#include <controller/supplier/supplier_contract_controller.h>
#include <service/supplier/supplier_contract_service.h>

void SupplierContractController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/supplier_contract/create")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, SupplierContractDTO::required_fields);
            
            auto supplier_contract_dto = SupplierContractDTO::from_json(j);
            
            auto res = SupplierContractService::create(supplier_contract_dto);
            return utils::to_response(res, 201);
        });
        
    CROW_ROUTE(app, "/api/supplier_contract/update")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, SupplierContractDTO::required_fields);
            
            auto supplier_contract_dto = SupplierContractDTO::from_json(j);
            auto supplier_contract_id = supplier_contract_dto.supplier_contract_id;
            
            auto res = SupplierContractService::updateBySupplierContractId(supplier_contract_id, supplier_contract_dto);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/supplier_contract/remove")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);
            // 检查必填字段
            CHECK_REQUIRED_FIELD(j, "supplier_contract_id");
            
            auto supplier_contract_id = j.at("supplier_contract_id").get<ex_id_type>();
            
            auto res = SupplierContractService::removeBySupplierContractId(supplier_contract_id);
            
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/supplier_contract/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);

            CHECK_REQUIRED_FIELD(j, "page");
            CHECK_REQUIRED_FIELD(j, "page_size");

            int page = j.value("page", 1);
            int page_size = j.value("page_size", 10);

            auto res = SupplierContractService::getByPage(page, page_size);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/supplier_contract/getAll")
        .methods("GET"_method)([]() {
            auto res = SupplierContractService::getAll();
            return utils::to_response(res, 200);
        });
        
    // 其他路由...
}
