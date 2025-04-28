#include <repository/goods/goods_repository.h>

// 通用 CRUD（internal）
insert_ret_type GoodsRepository::create(const GoodsDTO &goods_dto) {
  return _insert(goods_dto);
}

select_ret_type<GoodsDTO> GoodsRepository::getById(id_type id) {
  return _select(db::goods{}.id == id);
}

update_ret_type GoodsRepository::updateByGoodsId(id_type id, const GoodsDTO &goods_dto) {
  return _update(goods_dto, db::goods{}.id == id);
}

delete_ret_type GoodsRepository::removeById(id_type id) {
  return _remove(db::goods{}.id == id);
}

bool GoodsRepository::existsById(id_type id) {
  return _exists(db::goods{}.id == id);
}

// 面向业务 CRUD（external）
select_ret_type<GoodsDTO> GoodsRepository::getByGoodsId(const std::string &goods_id) {
  return _select(db::goods{}.goods_id == goods_id);
}

select_ret_type<GoodsDTO> GoodsRepository::getByName(const std::string &goods_name) {
  return _select(db::goods{}.goods_name == goods_name);
}

update_ret_type GoodsRepository::updateByGoodsId(const std::string &goods_id, const GoodsDTO &goods_dto) {
  return _update(goods_dto, db::goods{}.goods_id == goods_id);
}

delete_ret_type GoodsRepository::removeByGoodsId(const std::string &goods_id) {
  return _remove(db::goods{}.goods_id == goods_id);
}

bool GoodsRepository::existsByGoodsId(const std::string &goods_id) {
  return _exists(db::goods{}.goods_id == goods_id);
}

// other
select_ret_type<GoodsDTO> GoodsRepository::getAll() {
  return _select(db::goods{}.id >= 0);
}

select_ret_type<GoodsDTO> GoodsRepository::getByPage(count_type page_size, count_type offset) {
  return _select_from(db::goods{}.id >= 0, page_size, offset);
}

count_type GoodsRepository::count() {
  return _count();
}

// 多表查询商品详细信息
select_ret_type<GoodsDetailInfo>
GoodsRepository::getGoodsDetailInfoByGoodsId(const std::string &goods_id) {
  auto data = utils::DataBaseHelper::execute<select_ret_type<GoodsDetailInfo>>(
      [](const utils::pooled_conn_ptr_type &conn,
         const std::string &goods_id) {
        select_ret_type<GoodsDetailInfo> gi_list;

        db::goods goods{};
        db::inventory inventory{};
        db::unit unit{};
        db::warehouse warehouse{};
        db::goods_category category{};

        // 获取商品详细信息
        auto rows = (*conn)(
            sqlpp::select(goods.goods_id, goods.goods_name,
                          goods.shelf_life_days, inventory.quantity,
                          unit.unit_name, warehouse.warehouse_id,
                          warehouse.warehouse_name, warehouse.location,
                          category.goods_category_name)
                .from(inventory.join(goods)
                          .on(goods.id == inventory.goods_rk_id)
                          .join(warehouse)
                          .on(warehouse.id == inventory.warehouse_rk_id)
                          .join(unit)
                          .on(unit.id == goods.unit_rk_id)
                          .join(category)
                          .on(category.id == goods.category_rk_id))
                .where(goods.goods_id == goods_id));

        // 将查询结果转化为 GoodsDetailInfo 对象并填充到 gi_list
        for (auto &row : rows) {
          gi_list.push_back(
              GoodsDetailInfo{.goods_id = row.goods_id,
                              .goods_name = row.goods_name,
                              .shelf_life_days = row.shelf_life_days,
                              .unit = row.unit_name,
                              .warehouse_id = row.warehouse_id,
                              .warehouse_name = row.warehouse_name,
                              .location = row.location,
                              .category = row.goods_category_name});
        }
        return gi_list;
      },
      goods_id);
  return data;
}
