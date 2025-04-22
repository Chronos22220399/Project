#include <controller/goods_category_controller.h>
#include <service/goods_category_service.h>

void GoodsCategoryController::registerRoutes(crow::SimpleApp &app) {
  // add goods
  CROW_ROUTE(app, "/goods_category/add")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsCategoryService::addCategory(req.body);
      });

  // get all category
  CROW_ROUTE(app, "/goods_category/get_all")
      .methods("GET"_method)([](const crow::request &req) {
        return GoodsCategoryService::getAllCategory();
      });

  // get goods
  CROW_ROUTE(app, "/goods_category/get")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsCategoryService::getCategoryByPage(req.body);
      });

  // other routes
}
