#include <controller/goods/goods_controller.h>
#include <service/goods/goods_service.h>

void GoodsController::registerRoutes(crow::SimpleApp &app)
{

  // MARK: 商品创建接口 - POST /api/goods/create
  //
  // 请求JSON：
  // {
  //   "goods_name": string,    // 必填
  //   "category_id": string,   // 必填（外部ID）
  //   "supplier_id": string,   // 必填（外部ID）
  //   "unit_id": string,       // 必填（单位外部ID）
  //   "shelf_life_days": int,  // 必填（保质期天数 >=0）
  //   "barcode": string,       // 必填（商品条码）
  //   "image_url": string,     // 必填（商品图片URL）
  //   "description": string    // 必填（商品描述）
  // }
  //
  // 成功响应 (201):
  // {
  //   "code": 201,
  //   "data": {
  //     "goods_id": "Gxxxx",   // 外部ID（字符串）
  //     "create_time": "ISO8601时间"
  //   }
  // }
  //
  // 错误响应：
  // 400 - JSON解析失败/字段缺失/数值非法
  // 500 - 数据库错误
  CROW_ROUTE(app, "/api/goods/create")
      .methods("POST"_method)([](const crow::request &req)
                              { return GoodsService::create(req.body); });

  // MARK: 分页查询接口 - POST /api/goods/get_by_page
  //
  // 请求JSON：
  // {
  //   "page":      int?,  // 页码（>=1，默认1）
  //   "page_size": int?   // 每页数量（5-100，默认20）
  // }
  //
  // 成功响应 (200):
  // {
  //   "code": 200,
  //   "data": {
  //     "total": 235,         // 总商品数
  //     "current_page": 2,    // 当前页码
  //     "page_size": 20,      // 实际使用的分页大小
  //     "total_pages": 12,    // 总页数
  //     "items": [{
  //       "goods_id": "62d1a9d8e7b4b7712a6e3d7a",  // 外部ID(string)
  //       "goods_name": "商品示例",
  //       "category_name": "食品类",
  //       "stock": 100,       // 当前库存
  //       "external_info": {  // 外部关联信息（不暴露内部ID）
  //         "supplier_code": "SP-8848",
  //         "warehouse_code": "WH-SH01"
  //       }
  //     }]
  //   }
  // }
  //
  // 错误响应示例 (400 参数错误):
  // {
  //   "code": 400,
  //   "error": "INVALID_PAGINATION",
  //   "detail": "page_size must between 5 and 100"
  // }
  CROW_ROUTE(app, "/api/goods/get_by_page")
      .methods("POST"_method)([](const crow::request &req)
                              { return GoodsService::getByPage(req.body); });

  // MARK: 获取全部商品概要信息 - GET /api/goods/get_all
  //
  // 成功响应 (200):
  // {
  //   "code": 200,
  //   "data": [
  //     {
  //       "goods_id": "Gxxxx",
  //       "goods_name": "商品名称",
  //       "category_name": "分类名称",
  //       "stock": 100,
  //       "external_info": {
  //         "supplier_code": "SP-8848",
  //         "warehouse_code": "WH-SH01"
  //       }
  //     }
  //   ]
  // }
  //
  // 错误响应：
  // 500 - 数据库查询失败
  CROW_ROUTE(app, "/api/goods/get_all")
      .methods("GET"_method)(
          [](const crow::request &req)
          { return GoodsService::getAll(); });

  // MARK: 获取商品详细信息 - POST /api/goods/get_goods_detail_info
  //
  // 请求JSON：
  // {
  //   "goods_id": string  // 必填（商品外部ID）
  // }
  //
  // 成功响应 (200):
  // {
  //   "code": 200,
  //   "data": {
  //     "goods_id": "Gxxxx",
  //     "goods_name": "商品名称",
  //     "quantity": 1000,         // 库存总量
  //     "unit": "件",             // 计量单位
  //     "warehouse_name": "上海仓库",
  //     "location": "A区-12号货架",
  //     "shelf_life_days": 365    // 保质期天数
  //   }
  // }
  //
  // 错误响应：
  // 400 - 商品ID缺失或格式错误
  // 404 - 商品不存在
  // 500 - 数据库查询失败
  CROW_ROUTE(app, "/api/goods/get_goods_detail_info")
      .methods("POST"_method)([](const crow::request &req)
                              { return GoodsService::getGoodsDetailInfoById(req.body); });

  // other routes
}
