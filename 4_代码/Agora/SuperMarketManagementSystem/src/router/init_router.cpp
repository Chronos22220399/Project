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
#include <controller/warehouse/stock_in_controller.h>

// init all the routers
void initRouters(crow::SimpleApp &app) {
  // register goods router
  GoodsController::registerRoutes(app);

  // register goods_category router
  GoodsCategoryController::registerRoutes(app);

  // register goods_price router
  GoodsPriceController::registerRoutes(app);

  // register goods_promotion router
  GoodsPromotionController::registerRoutes(app);

  // register promotion router
  PromotionController::registerRoutes(app);

  // register inventory router
  InventoryController::registerRoutes(app);

  // register unit router
  UnitController::registerRoutes(app);

  // register warehouse router
  WarehouseController::registerRoutes(app);

  // register stock_in router
  StockInController::registerRoutes(app);
}
