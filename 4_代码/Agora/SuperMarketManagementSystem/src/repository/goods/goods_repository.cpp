#include <model/dto/goods/goods_dto.hpp>
#include <repository/goods/goods_repository.h>
using namespace std;

insert_ret_type GoodsRepository::create(const GoodsDTO &goods_dto) {
  return _insert(goods_dto);
}

select_ret_type<GoodsDTO> GoodsRepository::getAll() {
  return _select(db::goods{}.id >= 0);
}

select_ret_type<GoodsDTO> GoodsRepository::getByPage(count_type page_size,
                                                     count_type offset) {
  return _select_from(db::goods{}.id >= 0, page_size, offset);
}

count_type GoodsRepository::count() { return _count(); }

select_ret_type<GoodsDetailInfo>
GoodsRepository::getGoodsDetailInfoById(id_type goods_id) {
  auto data = utils::DataBaseHelper::execute<select_ret_type<GoodsDetailInfo>>(
      [](const utils::pooled_conn_ptr_type &conn, id_type goods_id) {
        select_ret_type<GoodsDetailInfo> gi_list;

        db::goods goods{};
        db::inventory inventory{};
        db::unit unit{};
        db::warehouse warehouse{};
        db::goods_category category{};

        // get the detail goods info
        auto rows =
            (*conn)(sqlpp::select(goods.goods_id, goods.goods_name,
                                  goods.shelf_life_days, inventory.quantity,
                                  unit.unit_name, warehouse.warehouse_id,
                                  warehouse.warehouse_name, warehouse.location,
                                  category.category_name)
                        .from(inventory.join(goods)
                                  .on(goods.id == inventory.goods_id)
                                  .join(warehouse)
                                  .on(warehouse.id == inventory.warehouse_id)
                                  .join(unit)
                                  .on(unit.id == goods.unit_id)
                                  .join(category)
                                  .on(category.id == goods.category_id))
                        .where(inventory.goods_id == goods_id));

        for (auto &row : rows) {
          gi_list.push_back(
              GoodsDetailInfo{.goods_id = row.goods_id,
                              .goods_name = row.goods_name,
                              .shelf_life_days = row.shelf_life_days,
                              .unit = row.unit_name,
                              .warehouse_id = row.warehouse_id,
                              .warehouse_name = row.warehouse_name,
                              .location = row.location,
                              .category = row.category_name});
        }
        return gi_list;
      },
      goods_id);
  return data;
}

bool GoodsRepository::exists(id_type goods_id) {
  return _exists(db::goods{}.id == goods_id);
}
