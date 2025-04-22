#include <controller/goods_category_controller.h>
#include <controller/goods_controller.h>
#include <router/init_router.h>

// init all the routers
void initRouters(crow::SimpleApp &app) {
  // regist goods router
  GoodsController::registerRoutes(app);

  // regist goods_category router
  GoodsCategoryController::registerRoutes(app);

  // regist warehouse router
}
