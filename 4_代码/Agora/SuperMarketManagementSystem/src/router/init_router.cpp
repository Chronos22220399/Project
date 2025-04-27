#include <router/init_router.h>
// common
#include <controller/common/unit_controller.h>
// goods
#include <controller/goods/goods_category_controller.h>
#include <controller/goods/goods_controller.h>
#include <controller/goods/goods_price_controller.h>
#include <controller/goods/goods_promotion_controller.h>
#include <controller/goods/inventory_controller.h>
#include <controller/goods/promotion_controller.h>
// warehouse
#include <controller/warehouse/warehouse_controller.h>

// init all the routers
void initRouters(crow::SimpleApp &app) {
  // regist goods router
  GoodsController::registerRoutes(app);

  // regist goods_category router
  GoodsCategoryController::registerRoutes(app);

  // regist goods_price router
  GoodsPriceController::registerRoutes(app);

  // regist goods_promotion router
  GoodsPromotionController::registerRoutes(app);

  // regist promotion router
  PromotionController::registerRoutes(app);

  // regist inventory router
  InventoryController::registerRoutes(app);

  // regist unit router
  UnitController::registerRoutes(app);

  // regist warehouse router
  WarehouseController::registerRoutes(app);

  // regist warehouse router
}
