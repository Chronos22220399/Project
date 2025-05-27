#include <controller/supplier/purchase_order_controller.h>
#include <service/supplier/purchase_order_service.h>

void PurchaseOrderController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/purchase_order/create")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, PurchaseOrderDTO::required_fields);
            
            auto purchase_order_dto = PurchaseOrderDTO::from_json(j);
            
            auto res = PurchaseOrderService::create(purchase_order_dto);
            return utils::to_response(res, 201);
        });
        
    CROW_ROUTE(app, "/api/purchase_order/update")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, PurchaseOrderDTO::required_fields);
            
            auto purchase_order_dto = PurchaseOrderDTO::from_json(j);
            auto purchase_order_id = purchase_order_dto.purchase_order_id;
            
            auto res = PurchaseOrderService::updateByPurchaseOrderId(purchase_order_id, purchase_order_dto);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/purchase_order/remove")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);
            // 检查必填字段
            CHECK_REQUIRED_FIELD(j, "purchase_order_id");
            
            auto purchase_order_id = j.at("purchase_order_id").get<ex_id_type>();
            
            auto res = PurchaseOrderService::removeByPurchaseOrderId(purchase_order_id);
            
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/purchase_order/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);

            CHECK_REQUIRED_FIELD(j, "page");
            CHECK_REQUIRED_FIELD(j, "page_size");

            int page = j.value("page", 1);
            int page_size = j.value("page_size", 10);

            auto res = PurchaseOrderService::getByPage(page, page_size);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/purchase_order/getAll")
        .methods("GET"_method)([]() {
            auto res = PurchaseOrderService::getAll();
            return utils::to_response(res, 200);
        });
        
    // 其他路由...
}
