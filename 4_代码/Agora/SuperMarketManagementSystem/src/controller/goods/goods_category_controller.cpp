#include <controller/goods/goods_category_controller.h>
#include <service/goods/goods_category_service.h>

void GoodsCategoryController::registerRoutes(crow::SimpleApp &app) {
  // MARK: 商品分类创建接口 - POST /api/goods_category/create
  //
  // 请求JSON：
  // {
  //   "category_name": string,           // 必填 分类名称
  //   "category_description": string,    // 必填 分类描述
  //   "parent_category_id": string       // 必填
  //   上级分类外部ID（无则为"0"或类似约定值）
  // }
  //
  // 成功响应 (201):
  // {
  //   "code": 201,
  //   "data": {
  //     "goods_category_id": "GCxxxx",   // 新创建的分类外部ID
  //     "create_time": "ISO8601时间"
  //   }
  // }
  //
  // 错误响应：
  // 400 - JSON解析失败/字段缺失
  // 500 - 数据库错误
  CROW_ROUTE(app, "/api/goods_category/create")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsCategoryService::create(req.body);
      });

  // MARK: 获取全部商品分类信息 - GET /api/goods_category/get_all
  //
  // 成功响应 (200):
  // {
  //   "success": true,
  //   "total": 3,          // 分类总数
  //   "data": [
  //     {
  //       "goods_category_id": "GCxxxx",
  //       "category_name": "食品类",
  //       "category_description": "可食用商品",
  //       "parent_category_id": "0"
  //     },
  //     ...
  //   ]
  // }
  //
  // 错误响应：
  // 500 - 数据库查询失败
  CROW_ROUTE(app, "/api/goods_category/get_all")
      .methods("GET"_method)([](const crow::request &req) {
        return GoodsCategoryService::getAll();
      });

  // MARK: 商品分类分页查询接口 - POST /api/goods_category/get_by_page
  //
  // 请求JSON：
  // {
  //   "page": int?,        // 页码，>=1，默认1
  //   "page_size": int?    // 每页数量，>=1，默认10
  // }
  //
  // 成功响应 (200):
  // {
  //   "success": true,
  //   "total": 45,           // 分类总数
  //   "page": 1,             // 当前页码
  //   "page_size": 10,       // 当前分页数量
  //   "data": [
  //     {
  //       "goods_category_id": "GCxxxx",
  //       "category_name": "食品类",
  //       "category_description": "可食用商品",
  //       "parent_category_id": "0"
  //     },
  //     ...
  //   ]
  // }
  //
  // 错误响应：
  // 400 - 参数非法（如 page 或 page_size 非法）
  // 500 - 数据库查询失败
  CROW_ROUTE(app, "/api/goods_category/get_by_page")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsCategoryService::getByPage(req.body);
      });

  // MARK: 删除商品分类接口 - POST /api/goods_category/remove
  //
  // 请求JSON：
  // {
  //   "goods_category_id": string    // 必填，商品分类外部ID
  // }
  //
  // 成功响应 (200):
  // {
  //   "code": 200
  // }
  //
  // 错误响应：
  // 400 - JSON解析失败/缺少goods_category_id
  // 404 - 分类不存在
  // 500 - 数据库删除异常
  CROW_ROUTE(app, "/api/goods_category/remove")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsCategoryService::removeByGoodsCategoryId(req.body);
      });

  // MARK: 修改商品分类接口 - POST /api/goods_category/update
  //
  // 请求JSON：
  // {
  //   "goods_category_id": string,        // 必填，商品分类外部ID
  //   "category_name": string,            // 必填，分类名称
  //   "category_description": string,     // 必填，分类描述
  //   "parent_category_id": string        // 必填，上级分类外部ID
  // }
  //
  // 成功响应 (200):
  // {
  //   "code": 200
  // }
  //
  // 错误响应：
  // 400 - JSON解析失败/缺少必填字段
  // 404 - 分类不存在
  // 500 - 数据库更新异常
  CROW_ROUTE(app, "/api/goods_category/update")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsCategoryService::updateByGoodsCategoryId(req.body);
      });

  // other routes
}
