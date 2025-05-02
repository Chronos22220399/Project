#include <controller/goods/goods_category_controller.h>
#include <service/goods/goods_category_service.h>

void GoodsCategoryController::registerRoutes(crow::SimpleApp &app) {
  // add goods
  CROW_ROUTE(app, "/api/goods_category/add")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsCategoryService::create(req.body);
      });

  // get all category
  CROW_ROUTE(app, "/api/goods_category/get_all")
      .methods("GET"_method)([](const crow::request &req) {
        return GoodsCategoryService::getAll();
      });

  // get category by page
  CROW_ROUTE(app, "/api/goods_category/get_by_page")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsCategoryService::getByPage(req.body);
      });

  // delete category by
  CROW_ROUTE(app, "/api/goods_category/remove")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsCategoryService::removeByGoodsCategoryId(req.body);
      });

  // update category
  CROW_ROUTE(app, "/api/goods_category/update")
      .methods("POST"_method)([](const crow::request &req) {
        return GoodsCategoryService::updateByGoodsCategoryId(req.body);
      });

  // other routes
}
