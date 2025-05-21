#include <controller/goods/goods_price_controller.h>
#include <nlohmann/json.hpp>
#include <service/goods/goods_price_service.h>

const std::vector<std::string> required_fields = {"goods_id", "price",
                                                  "start_time", "note"};

void GoodsPriceController::registerRoutes(crow::SimpleApp& app)
{
  // MARK: 商品价格创建接口 - POST /api/goods_price/create
  //
  // 请求JSON：
  // {
  //   "goods_id": string,        // 必填，商品外部ID
  //   "price": double,           // 必填，商品价格
  //   "start_time": string,      // 必填，价格生效时间（ISO8601格式）
  //   "note": string             // 必填，备注信息
  // }
  //
  // 成功响应 (200):
  // {
  //   "code": 200
  // }
  //
  // 错误响应：
  // 400 - JSON解析失败/缺少必填字段
  // 404 - 商品不存在
  // 405 - 商品未找到（逻辑检查）
  // 409 - 商品价格已存在
  // 500 - 数据库插入异常
  CROW_ROUTE(app, "/api/goods_price/create")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      CHECK_REQUIRED_FIELDS(j, required_fields);

      auto goods_price_dto = GoodsPriceDTO::from_json(j);
      auto res = GoodsPriceService::create(goods_price_dto);

      return utils::to_response(res, 201);
    });


  // MARK: 删除商品价格接口 - POST /api/goods_price/remove
  //
  // 请求JSON：
  // {
  //   "goods_id": string    // 必填，商品外部ID
  // }
  //
  // 成功响应 (200):
  // {
  //   "code": 200
  // }
  //
  // 错误响应：
  // 400 - JSON解析失败/缺少goods_id
  // 404 - 商品不存在或商品价格不存在
  // 500 - 数据库删除异常
  CROW_ROUTE(app, "/api/goods_price/remove")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查必填字段
      CHECK_REQUIRED_FIELD(j, "goods_id");
      auto goods_id = j.at("goods_id").get<ex_id_type>();

      auto res = GoodsPriceService::removeByGoodsId(goods_id);
      return utils::to_response(res, 200);
    });

  // MARK: 修改商品价格接口 - POST /api/goods_price/update
  //
  // 请求JSON：
  // {
  //   "goods_id": string,        // 必填，商品外部ID
  //   "price": double,           // 必填，新的商品价格
  //   "start_time": string,      // 必填，价格生效时间（ISO8601格式）
  //   "note": string             // 必填，备注信息
  // }
  //
  // 成功响应 (200):
  // {
  //   "code": 200
  // }
  //
  // 错误响应：
  // 400 - JSON解析失败/缺少必填字段
  // 404 - 商品不存在或商品价格不存在
  // 500 - 数据库更新异常
  CROW_ROUTE(app, "/api/goods_price/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查必填字段
      CHECK_REQUIRED_FIELDS(j, required_fields);

      auto goods_price_dto = GoodsPriceDTO::from_json(j);
      auto res = GoodsPriceService::updateByGoodsRKId(
        goods_price_dto.goods_rk_id, goods_price_dto);

      return utils::to_response(res, 200);
    });

  // MARK: 分页获取商品价格接口 - POST /api/goods_price/get_by_page
  //
  // 请求JSON：
  // {
  //   "page": int?,        // 页码，>=1，默认1
  //   "page_size": int?    // 每页数量，>=1，默认10
  // }
  //
  // 成功响应 (200):
  // {
  //   "code": 200,
  //   "data": {
  //     "success": true,
  //     "total": 100,         // 商品价格总数
  //     "page": 1,            // 当前页码
  //     "page_size": 10,      // 每页数量
  //     "items": [
  //       {
  //         "goods_price_id": "GPxxxx",
  //         "goods_id": "Gxxxx",
  //         "price": 100.5,
  //         "start_time": "2025-05-01T12:00:00Z",
  //         "note": "备注信息"
  //       },
  //       {
  //       ...
  //     ]
  //   }
  // }
  //
  // 错误响应：
  // {
  //   "code": 400,    // 参数非法（如 page 或 page_size 非法）
  //   "data": null
  // }
  // {
  //   "code": 500,    // 数据库查询失败
  //   "data": null
  // }
  CROW_ROUTE(app, "/api/goods_price/get_by_page")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      // 解析分页参数并设置默认值
      int page = j.value("page", 1);
      int page_size = j.value("page_size", 10);

      auto res = GoodsPriceService::getByPage(page, page_size);
      return utils::to_response(res, 200);
    });

  // Not implemented !
  CROW_ROUTE(app, "/api/goods_price/get_all").methods("GET"_method)([]() {
    auto res = GoodsPriceService::getAll();
    return crow::response(501, "Not implemented yet.");
  });

  // 其他路由...
}
