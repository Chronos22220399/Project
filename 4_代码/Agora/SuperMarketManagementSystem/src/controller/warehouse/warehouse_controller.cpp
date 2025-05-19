#include <controller/warehouse/warehouse_controller.h>
#include <service/warehouse/warehouse_service.h>

// MARK: 仓库创建接口 - POST /api/warehouse/create
//
// 请求JSON：
// {
//   "warehouse_name": string,        // 必填 仓库名称
//   "location": string,              // 必填 地理位置
//   "total_slots": int,              // 必填 总货位数
//   "available_slots": int,          // 必填 可用货位数
//   "manager": string,               // 必填 负责人
//   "description": string            // 必填 仓库描述
// }
//
// 成功响应 (201):
// {
//   "code": 201,
//   "data": {
//     "warehouse_id": "W-xxxx",       // 新创建的仓库ID
//     "warehouse_name": string,
//     "location": string,
//     "total_slots": int,
//     "available_slots": int,
//     "manager": string,
//     "description": string
//   }
// }
//
// 错误响应：
// {
//   "code": 400,    // 请求JSON解析失败或字段缺失
//   "data": null
// }
// {
//   "code": 500,    // 数据库错误
//   "data": null
// }
void WarehouseController::registerRoutes(crow::SimpleApp &app) {
  CROW_ROUTE(app, "/api/warehouse/create")
      .methods("POST"_method)([](const crow::request &req) {
        return WarehouseService::create(req.body);
      });

  // MARK: 仓库更新接口 - POST /api/warehouse/update
  //
  // 请求JSON：
  // {
  //   "warehouse_id": string,         // 必填 仓库ID
  //   "warehouse_name": string,       // 必填 仓库名称
  //   "location": string,             // 必填 地理位置
  //   "total_slots": int,             // 必填 总货位数
  //   "available_slots": int,         // 必填 可用货位数
  //   "manager": string,              // 必填 负责人
  //   "description": string           // 必填 仓库描述
  // }
  //
  // 成功响应 (200):
  // {
  //   "code": 200,
  //   "data": null
  // }
  //
  // 错误响应：
  // {
  //   "code": 400,    // 请求JSON解析失败或字段缺失
  //   "data": null
  // }
  // {
  //   "code": 404,    // 仓库不存在
  //   "data": null
  // }
  // {
  //   "code": 500,    // 数据库更新异常
  //   "data": null
  // }
  CROW_ROUTE(app, "/api/warehouse/update")
      .methods("POST"_method)([](const crow::request &req) {
        return WarehouseService::updateByWarehouseId(req.body);
      });

  // MARK: 仓库分页查询接口 - POST /api/warehouse/get_by_page
  //
  // 请求JSON：
  // {
  //   "page": int,         // 必填 页码，>=1
  //   "page_size": int     // 必填 每页数量，>=1
  // }
  //
  // 成功响应 (200):
  // {
  //   "code": 200,
  //   "data": {
  //     "total": int,               // 仓库总数
  //     "current_page": int,        // 当前页码
  //     "page_size": int,           // 每页数量
  //     "total_pages": int,         // 总页数
  //     "items": [                  // 当前页的仓库列表
  //       {
  //         "warehouse_id": string,
  //         "warehouse_name": string,
  //         "location": string,
  //         "total_slots": int,
  //         "available_slots": int,
  //         "manager": string,
  //         "description": string
  //       },
  //       ...
  //     ]
  //   }
  // }
  //
  // 错误响应：
  // {
  //   "code": 400,    // 参数非法（如page或page_size非法）
  //   "data": null
  // }
  // {
  //   "code": 500,    // 数据库查询异常
  //   "data": null
  // }
  CROW_ROUTE(app, "/api/warehouse/get_by_page")
      .methods("POST"_method)([](const crow::request &req) {
        return WarehouseService::getByPage(req.body);
      });

  // MARK: 获取所有仓库信息接口 - GET /api/warehouse/get_all
  //
  // 成功响应 (200):
  // {
  //   "code": 200,
  //   "data": {
  //     "success": true,
  //     "total": int,                // 仓库总数
  //     "items": [
  //       {
  //         "warehouse_id": string,
  //         "warehouse_name": string,
  //         "location": string,
  //         "total_slots": int,
  //         "available_slots": int,
  //         "manager": string,
  //         "description": string
  //       },
  //       ...
  //     ]
  //   }
  // }
  //
  // 错误响应：
  // {
  //   "code": 500,    // 数据库查询异常
  //   "data": null
  // }
  CROW_ROUTE(app, "/api/warehouse/get_all").methods("GET"_method)([]() {
    return WarehouseService::getAll();
  });

  // 其他路由...
}
