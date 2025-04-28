#include <repository/goods/goods_price_repository.h>

// 通用 CRUD（internal）
insert_ret_type
GoodsPriceRepository::create(const GoodsPriceDTO &goods_price_dto) {
  return _insert(goods_price_dto);
}

select_ret_type<GoodsPriceDTO> GoodsPriceRepository::getById(id_type id) {
  return _select(db::goods_price{}.id == id);
}

update_ret_type
GoodsPriceRepository::updateById(id_type id,
                                 const GoodsPriceDTO &goods_price_dto) {
  return _update(goods_price_dto, db::goods_price{}.id == id);
}

delete_ret_type GoodsPriceRepository::removeById(id_type id) {
  return _remove(db::goods_price{}.id == id);
}

bool GoodsPriceRepository::existsById(id_type id) {
  return _exists(db::goods_price{}.id == id);
}

// 面向业务 CRUD（external）
select_ret_type<GoodsPriceDTO>
GoodsPriceRepository::getByGoodsRKId(id_type goods_rk_id) {
  return _select(db::goods_price{}.goods_rk_id == goods_rk_id);
}

update_ret_type
GoodsPriceRepository::updateByGoodsRKId(id_type goods_rk_id,
                                        const GoodsPriceDTO &goods_price_dto) {
  return _update(goods_price_dto, db::goods_price{}.goods_rk_id == goods_rk_id);
}

delete_ret_type GoodsPriceRepository::removeByGoodsRKId(id_type goods_rk_id) {
  return _remove(db::goods_price{}.goods_rk_id == goods_rk_id);
}

bool GoodsPriceRepository::existsByGoodsRKId(id_type goods_rk_id) {
  return _exists(db::goods_price{}.goods_rk_id == goods_rk_id);
}

// other
select_ret_type<GoodsPriceDTO> GoodsPriceRepository::getAll() {
  return _select(db::goods_price{}.id >= 0);
}

select_ret_type<GoodsPriceDTO>
GoodsPriceRepository::getByPage(count_type page_size, count_type offset) {
  return _select_from(db::goods_price{}.id >= 0, page_size, offset);
}

count_type GoodsPriceRepository::count() { return _count(); }
