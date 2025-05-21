#include <controller/goods/promotion_controller.h>
#include <service/goods/promotion_service.h>


void PromotionController::registerRoutes(crow::SimpleApp& app)
{
  // MARK: 创建促销活动接口 - POST /api/promotion/create
  CROW_ROUTE(app, "/api/promotion/create")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查必填字段
      CHECK_REQUIRED_FIELDS(j, PromotionDTO::required_fields);

      auto promotion_dto = PromotionDTO::from_json(j);

      auto res = PromotionService::create(promotion_dto);
      return utils::to_response(res, 201);
    });

  // MARK: 删除促销活动接口 - POST /api/promotion/remove
  //
  // 请求JSON：
  // {
  //   "promotion_id": string   // 必填，促销活动ID
  // }
  //
  // 成功响应 (200):
  // {
  //   "code": 200
  // }
  //
  // 错误响应：
  // {
  //   "code": 400    // JSON解析失败/缺少 promotion_id
  // }
  // {
  //   "code": 500    // 数据库删除失败
  // }
  CROW_ROUTE(app, "/api/promotion/remove")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      // 检查必填字段
      CHECK_REQUIRED_FIELD(j, "promotion_id");
      auto promotion_id = j.at("promotion_id").get<ex_id_type>();

      auto res = PromotionService::removeByPromotionId(promotion_id);

      return utils::to_response(res, 200);
    });

  // MARK: 更新促销活动接口 - POST /api/promotion/update
  //
  // 请求JSON：
  // {
  //   "promotion_id": string,   // 必填，促销活动ID
  //   "name": string,           // 必填，促销活动名称
  //   "description": string,    // 必填，促销活动描述
  //   "type": string,           // 必填，活动类型（"discount" 或 "full
  //   reduction"） "start_time": string,     //
  //   必填，活动开始时间（ISO8601格式） "end_time": string,       //
  //   必填，活动结束时间（ISO8601格式） "status": string          //
  //   必填，状态（"active"、"expired"、"draft"）
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
  //   "code": 404    // 促销活动不存在
  // }
  // {
  //   "code": 500    // 数据库更新失败
  // }
  CROW_ROUTE(app, "/api/promotion/update")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);
      // 检查必填字段
      CHECK_REQUIRED_FIELDS(j, PromotionDTO::required_fields);

      auto promotion_dto = PromotionDTO::from_json(j);
      auto promotion_id = promotion_dto.promotion_id;

      auto res =
        PromotionService::updateByPromotionId(promotion_id, promotion_dto);
      return utils::to_response(res, 200);
    });

  // MARK: 分页获取促销活动接口 - POST /api/promotion/get_by_page
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
  //     "total": 100,         // 促销活动总数
  //     "page": 1,            // 当前页码
  //     "page_size": 10,      // 每页数量
  //     "items": [
  //       {
  //         "promotion_id": "Pxxxx",
  //         "name": "Promotion A",
  //         "description": "Discount promotion",
  //         "type": "discount",
  //         "start_time": "2025-05-01T00:00:00",
  //         "end_time": "2025-05-10T23:59:59",
  //         "status": "active"
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
  CROW_ROUTE(app, "/api/promotion/get_by_page")
    .methods("POST"_method)([](const crow::request& req) {
      nlohmann::json j;
      auto& body = req.body;
      CHECK_AND_GET_JSON(j);

      // 获取分页参数并设置默认值
      int page = j.value("page", 1);
      int page_size = j.value("page_size", 10);

      auto res = PromotionService::getByPage(page, page_size);
      return utils::to_response(res, 200);
    });

  // MARK: 获取所有促销活动接口 - GET /api/promotion/get_all
  //
  // 成功响应 (200):
  // {
  //   "code": 200,
  //   "data": {
  //     "success": true,
  //     "total": 100,         // 促销活动总数
  //     "items": [
  //       {
  //         "promotion_id": "Pxxxx",
  //         "name": "Promotion A",
  //         "description": "Discount promotion",
  //         "type": "discount",
  //         "start_time": "2025-05-01T00:00:00",
  //         "end_time": "2025-05-10T23:59:59",
  //         "status": "active"
  //       },
  //       ...
  //     ]
  //   }
  // }
  //
  // 错误响应：
  // {
  //   "code": 500    // 数据库查询失败
  // }
  CROW_ROUTE(app, "/api/promotion/get_all").methods("GET"_method)([]() {
    auto res = PromotionService::getAll();
    return utils::to_response(res, 200);
  });

  // 其他路由...
}
