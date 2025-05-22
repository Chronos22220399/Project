#include <controller/goods/goods_category_controller.h>
#include <service/goods/goods_category_service.h>

const std::vector<std::string> required_fields = {
  "goods_category_id", "goods_category_name", "goods_category_description",
  "parent_category_id"};

void GoodsCategoryController::registerRoutes(crow::SimpleApp& app)
{
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
  // {
  //   "code": 400,    // JSON解析失败/字段缺失
  //   "data": null
  // }
  // {
  //   "code": 500,    // 数据库错误
  //   "data": null
  // }
  CROW_ROUTE(app, "/api/goods_category/create")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      // 检查并解析JSON，失败自动返回400
      CHECK_AND_GET_JSON(j);
      // 检查必填字段
      CHECK_REQUIRED_FIELDS(j, required_fields);
      auto gc_dto = GoodsCategoryDTO::from_json(j);
      gc_dto.goods_category_id = utils::create_id("GC");  // 生成外部ID

      auto res = GoodsCategoryService::create(gc_dto);
      return utils::to_response(res, 201);
    });


  // MARK: 获取全部商品分类信息 - GET /api/goods_category/get_all
  //
  // 成功响应 (200):
  // {
  //   "code": 200,
  //   "data": {
  //     "success": true,
  //     "total": 3,          // 分类总数
  //     "categories": [
  //       {
  //         "goods_category_id": "GCxxxx",
  //         "category_name": "食品类",
  //         "category_description": "可食用商品",
  //         "parent_category_id": "0"
  //       },
  //       ...
  //     ]
  //   }
  // }
  //
  // 错误响应：
  // {
  //   "code": 500,    // 数据库查询失败
  //   "data": null
  // }
  CROW_ROUTE(app, "/api/goods_category/get_all")
    .methods("GET"_method)([](const crow::request& req) {
      auto res = GoodsCategoryService::getAll();
      return utils::to_response(res, 200);
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
  //   "code": 200,
  //   "data": {
  //     "success": true,
  //     "total": 45,           // 分类总数
  //     "page": 1,             // 当前页码
  //     "page_size": 10,       // 当前分页数量
  //     "categories": [
  //       {
  //         "goods_category_id": "GCxxxx",
  //         "category_name": "食品类",
  //         "category_description": "可食用商品",
  //         "parent_category_id": "0"
  //       },
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
  CROW_ROUTE(app, "/api/goods_category/get_by_page")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      int page = j.value("page", 1);
      int page_size = j.value("page_size", 10);
      if (page <= 0 || page_size <= 0) {
        return SET_ERR_RESPONSE(400, "Invalid page or page_size");
      }

      auto res = GoodsCategoryService::getByPage(page, page_size);
      return utils::to_response(res, 200);
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
  //   "code": 200,
  //   "data": null
  // }
  //
  // 错误响应：
  // {
  //   "code": 400,    // JSON解析失败/缺少goods_category_id
  //   "data": null
  // }
  // {
  //   "code": 404,    // 分类不存在
  //   "data": null
  // }
  // {
  //   "code": 500,    // 数据库删除异常
  //   "data": null
  // }
  CROW_ROUTE(app, "/api/goods_category/remove")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查并获取必填字段
      CHECK_REQUIRED_FIELD(j, "goods_category_id");
      auto goods_category_id = j.at("goods_category_id").get<ex_id_type>();

      auto res =
        GoodsCategoryService::removeByGoodsCategoryId(goods_category_id);
      return utils::to_response(res, 200);
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
  //   "code": 200,
  //   "data": null
  // }
  //
  // 错误响应：
  // {
  //   "code": 400,    // JSON解析失败/缺少必填字段
  //   "data": null
  // }
  // {
  //   "code": 404,    // 分类不存在
  //   "data": null
  // }
  // {
  //   "code": 500,    // 数据库更新异常
  //   "data": null
  // }
  CROW_ROUTE(app, "/api/goods_category/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查并获取必填字段
      CHECK_REQUIRED_FIELDS(j, required_fields);
      CHECK_REQUIRED_FIELD(j, "goods_category_id");
      auto gc_dto = GoodsCategoryDTO::from_json(j);
      auto goods_category_id = gc_dto.goods_category_id;

      auto res = GoodsCategoryService::updateByGoodsCategoryId(
        goods_category_id, gc_dto);
      return utils::to_response(res, 200);
    });

  // other routes
}
