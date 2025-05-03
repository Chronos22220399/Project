#include <chrono>
#include <common/global_id_cache.hpp>
#include <crow.h>
#include <future>
#include <iostream>
#include <repository/goods/promotion_repository.h>
#include <repository/warehouse/warehouse_repository.h>
#include <router/init_router.h>
#include <vector>
using namespace std;

// void insert_test_data() {
//   for (int i = 1; i <= 30; ++i) {
//     GoodsDTO dto;
//     dto.id = 0; // 假设自增主键由数据库生成
//     dto.goods_id = "G" + std::to_string(1000 + i);
//     dto.category_rk_id = i % 5 + 1; // 模拟 1~5 的分类 ID
//     dto.supplier_rk_id = i % 3 + 1; // 模拟 1~3 的供应商 ID
//     dto.unit_rk_id = i % 4 + 1;     // 模拟 1~4 的单位 ID
//     dto.goods_name = "测试商品" + std::to_string(i);
//     dto.shelf_life_days = 365; // 固定保质期
//     dto.barcode = "TESTBAR" + std::to_string(100000 + i);
//     dto.image_url = "http://example.com/image" + std::to_string(i) + ".jpg";
//     dto.description = "这是第 " + std::to_string(i) + " 个测试商品";
//
//     auto result = GoodsRepository::create(dto);
//     if (!result) {
//       std::cerr << "插入第 " << i << " 条数据失败: " << std::endl;
//     }
//   }
// }
//

void testPromotionCreation();
void testGoodsCreation();
void testWarehouseCreation();

void testCrowServer();

int main() {
  auto &cache = GlobalIdCache::getInstance();
  // regist goods
  cache.registForward("goods", &GoodsRepository::getInternalId);
  cache.registReverse("goods", &GoodsRepository::getExternalId);
  // regist goods_category
  cache.registForward("goods_category", &GoodsRepository::getInternalId);
  cache.registReverse("goods_category", &GoodsRepository::getExternalId);
  // regist promotion
  cache.registForward("promotion", &PromotionRepository::getInternalId);
  cache.registReverse("promotion", &PromotionRepository::getExternalId);
  // regist warehouse
  cache.registForward("warehouse", &WarehouseRepository::getInternalId);
  cache.registReverse("warehouse", &WarehouseRepository::getExternalId);

  // 先确保测试数据存在
  // const std::string wh_id = "WH-d337cae7-d53b-4be0-9e5d-8de553b65a14";
  // id_type expected_id = WarehouseRepository::getId(wh_id);

  testCrowServer();
  return 0;
}

void testWarehouseCreation() {
  WarehouseDTO warehouse{.id = 0,
                         .warehouse_id = utils::create_id("WH-"),
                         .warehouse_name = "Sample Warehouse",
                         .location = "Beijing"};

  bool createSuccess = WarehouseRepository::create(warehouse);
  cout << "创建仓库结果: " << boolalpha << createSuccess << endl;

  bool updateSuccess = WarehouseRepository::updateByWarehouseId(
      warehouse.warehouse_id, warehouse);
  cout << "更新仓库结果: " << boolalpha << updateSuccess << endl;
}

void testGoodsCreation() {
  GoodsDTO goods{
      .goods_id = utils::create_id("G-"),
      .category_rk_id = 0,
      .goods_name = "Sample Goods",
      .shelf_life_days = 10,
      .barcode = "123",
      .image_url = "none",
      .description = "This is a sample goods description.",
  };

  bool createSuccess = GoodsRepository::create(goods);
  cout << "创建商品结果: " << boolalpha << createSuccess << endl;

  bool updateSuccess = GoodsRepository::updateByGoodsId(goods.goods_id, goods);
  cout << "更新商品结果: " << boolalpha << updateSuccess << endl;
}

void testCrowServer() {
  crow::SimpleApp app;
  initRouters(app);
  app.multithreaded().port(utils::configManager.getPort()).run();
}

// void testGoodsRepository() {
//   cout << "商品总数: " << GoodsRepository::count() << endl;
//   auto goodsList = GoodsRepository::getGoodsByPage(10, 0);
//   for (const auto& goods : goodsList) {
//     fmt::println("商品ID: {}\t名称: {}\t描述: {}",
//                  goods.goods_id, goods.goods_name, goods.description);
//   }
// }
