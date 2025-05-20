#include <controller/goods/inventory_controller.h>
#include <service/goods/inventory_service.h>


const std::vector<std::string> required_fields = {"goods_id", "warehouse_id",
                                                  "quantity"};

void InventoryController::registerRoutes(crow::SimpleApp& app)
{
  // MARK: 创建库存接口 - POST /api/inventory/create
  //
  // 请求JSON：
  // {
  //   "goods_id": string,       // 必填，商品外部ID
  //   "warehouse_id": string,   // 必填，仓库外部ID
  //   "quantity": int           // 必填，库存数量
  // }
  //
  // 成功响应 (201):
  // {
  //   "code": 201
  // }
  //
  // 错误响应：
  // {
  //   "code": 400    // JSON解析失败/缺少必填字段
  // }
  // {
  //   "code": 404    // 商品或仓库不存在
  // }
  // {
  //   "code": 500    // 数据库插入异常
  // }
  CROW_ROUTE(app, "/api/inventory/create")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查必填字段
      CHECK_REQUIRED_FIELDS(j, required_fields);

      auto inventory_dto = InventoryDTO::from_json(j);

      auto res = InventoryService::create(inventory_dto);

      return utils::to_response(res, 201);
    });


  // MARK: 修改库存接口 - POST /api/inventory/update
  //
  // 请求JSON：
  // {
  //   "goods_id": string,       // 必填，商品外部ID
  //   "warehouse_id": string,   // 必填，仓库外部ID
  //   "quantity": int           // 必填，库存数量
  // }
  //
  // 成功响应 (200):
  // {
  //   "code": 200
  // }
  //
  // 错误响应：
  // {
  //   "code": 400    // JSON解析失败/缺少必填字段
  // }
  // {
  //   "code": 404    // 商品或仓库不存在
  // }
  // {
  //   "code": 500    // 数据库更新异常
  // }
  CROW_ROUTE(app, "/api/inventory/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查并获取必填字段
      CHECK_REQUIRED_FIELDS(j, required_fields);
      auto inventory_dto = InventoryDTO::from_json(j);
      auto goods_rk_id = inventory_dto.goods_rk_id;

      auto res = InventoryService::updateByGoodsId(goods_rk_id, inventory_dto);
      return utils::to_response(res, 200);
    });

  // MARK: 获取指定商品库存接口 - POST /api/inventory/get_by_goods_id
  //
  // 请求JSON：
  // {
  //   "goods_id": string    // 必填，商品外部ID
  // }
  //
  // 成功响应 (200):
  // {
  //   "code": 200,
  //   "data": {
  //     "success": true,
  //     "total": 2,           // 库存记录总数
  //     "items": [
  //       {
  //         "goods_id": "Gxxxx",
  //         "warehouse_id": "Wxxxx",
  //         "quantity": 100
  //       },
  //       ...
  //     ]
  //   }
  // }
  //
  // 错误响应：
  // {
  //   "code": 400    // JSON解析失败/缺少goods_id
  // }
  // {
  //   "code": 404    // 商品不存在
  // }
  // {
  //   "code": 500    // 数据库查询异常
  // }
  CROW_ROUTE(app, "/api/inventory/get_by_goods_id")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELD(j, "goods_id");
      auto goods_id = j.at("goods_id").get<ex_id_type>();

      auto res = InventoryService::getByGoodsId(goods_id);

      return utils::to_response(res, 200);
    });

  // MARK: 获取指定仓库库存接口 - POST /api/inventory/get_by_warehouse_id
  //
  // 请求JSON：
  // {
  //   "warehouse_id": string    // 必填，仓库外部ID
  // }
  //
  // 成功响应 (200):
  // {
  //   "code": 200,
  //   "data": {
  //     "success": true,
  //     "total": 2,           // 库存记录总数
  //     "items": [
  //       {
  //         "goods_id": "Gxxxx",
  //         "warehouse_id": "Wxxxx",
  //         "quantity": 100
  //       },
  //       ...
  //     ]
  //   }
  // }
  //
  // 错误响应：
  // {
  //   "code": 400    // JSON解析失败/缺少warehouse_id
  // }
  // {
  //   "code": 404    // 仓库不存在
  // }
  // {
  //   "code": 500    // 数据库查询异常
  // }
  CROW_ROUTE(app, "/api/inventory/get_by_warehouse_id")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELD(j, "warehouse_id");
      auto warehouse_id = j.at("warehouse_id").get<ex_id_type>();

      auto res = InventoryService::getByGoodsId(warehouse_id);

      return utils::to_response(res, 200);
    });

  // MARK: 分页获取库存记录接口 - POST /api/inventory/get_by_page
  //
  // 请求JSON：
  // {
  //   "page": int,        // 页码，>=1，默认1
  //   "page_size": int    // 每页数量，>=1，默认10
  // }
  //
  // 成功响应 (200):
  // {
  //   "code": 200,
  //   "data": {
  //     "success": true,
  //     "total": 100,         // 库存记录总数
  //     "page": 1,            // 当前页码
  //     "page_size": 10,      // 每页数量
  //     "items": [ {
  //         "goods_id": "Gxxxx",
  //         "warehouse_id": "Wxxxx",
  //         "quantity": 100
  //       },
  //       ...
  //     ]
  //   }
  // }
  //
  // 错误响应：
  // {
  //   "code": 400    // 参数非法（如 page 或 page_size 非法）
  // }
  // {
  //   "code": 500    // 数据库查询失败
  // }
  CROW_ROUTE(app, "/api/inventory/get_by_page")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      // 解析分页参数并设置默认值
      int page = j.value("page", 1);
      int page_size = j.value("page_size", 10);

      auto res = InventoryService::getByPage(page, page_size);
      return utils::to_response(res, 200);
    });

  // Not implement !
  CROW_ROUTE(app, "/api/inventory/get_all").methods("GET"_method)([]() {
    auto res = InventoryService::getAll();
    return crow::response(501, "Not implemented yet.");
  });

  // 其他路由...
}
