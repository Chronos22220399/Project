#include <chrono>
#include <crow.h>
#include <repository/goods/goods_repository.h>
#include <repository/goods/promotion_repository.h>
#include <router/init_router.h>
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

int main() {
  PromotionDTO pdto{
      .promotion_name = "233",
      .description = "hhh",
      .type = "discount",
      .start_time = {},
      .end_time = {},
      .status = "active",
  };

  pdto.promotion_id = utils::create_id("P-");

  bool success = PromotionRepository::create(pdto);
  // bool success =
  //     PromotionRepository::updateByPromotionId(pdto.promotion_id, pdto);
  cout << "修改结果为: " << success << endl;

  // crow::SimpleApp app;
  //
  // std::uint16_t port = utils::configManager.getPort();
  //
  // initRouters(app);
  // app.multithreaded().port(port).run();
  // cout << GoodsRepository::count() << endl;
  // auto goods_list = GoodsRepository::getGoodsByPage(10, 0);
  // for (auto goods : goods_list) {
  //   fmt::println("goods_id: {}\tgoods_name: {}, description: {}",
  //                goods.goods_id, goods.goods_name, goods.description);
  // }
  return 0;
}
