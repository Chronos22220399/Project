#include <controller/warehouse/inventory_check_order_controller.h>
#include <service/warehouse/inventory_check_order_service.h>

void InventoryCheckOrderController::registerRoutes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/api/inventory_check_order/create")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, InventoryCheckOrderDTO::required_fields);
            
            auto inventory_check_order_dto = InventoryCheckOrderDTO::from_json(j);
            
            auto res = InventoryCheckOrderService::create(inventory_check_order_dto);
            return utils::to_response(res, 201);
        });
        
    CROW_ROUTE(app, "/api/inventory_check_order/update")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto &body = req.body;
            CHECK_AND_GET_JSON(j);
            CHECK_REQUIRED_FIELDS(j, InventoryCheckOrderDTO::required_fields);
            
            auto inventory_check_order_dto = InventoryCheckOrderDTO::from_json(j);
            auto inventory_check_order_id = inventory_check_order_dto.inventory_check_order_id;
            
            auto res = InventoryCheckOrderService::updateByInventoryCheckOrderId(inventory_check_order_id, InventoryCheckOrderDTO);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/inventory_check_order/remove")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);
            // 检查必填字段
            CHECK_REQUIRED_FIELD(j, "inventory_check_order_id");
            
            auto inventory_check_order_id = j.at("inventory_check_order_id").get<ex_id_type>();
            
            auto res = InventoryCheckOrderService::removeByInventoryCheckOrderId(inventory_check_order_id);
            
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/inventory_check_order/getByPage")
        .methods("POST"_method)([](const crow::request& req) {
            nlohmann::json j;
            auto& body = req.body;
            CHECK_AND_GET_JSON(j);

            CHECK_REQUIRED_FIELD(j, "page");
            CHECK_REQUIRED_FIELD(j, "page_size");

            int page = j.value("page", 1);
            int page_size = j.value("page_size", 10);

            auto res = InventoryCheckOrderService::getByPage(page, page_size);
            return utils::to_response(res, 200);
        });
        
    CROW_ROUTE(app, "/api/inventory_check_order/getAll")
        .methods("GET"_method)([]() {
            auto res = InventoryCheckOrderService::getAll();
            return utils::to_reponse(res, 200);
        });
        
    // 其他路由...
}
