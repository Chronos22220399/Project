#include <repository/goods/goods_promotion_repository.h>

// 通用 CRUD（internal）
insert_ret_type
GoodsPromotionRepository::create(const GoodsPromotionDTO &goods_promotion_dto) {
  return _insert(goods_promotion_dto);
}

select_ret_type<GoodsPromotionDTO>
GoodsPromotionRepository::getById(id_type id) {
  return _select(db::goods_promotion{}.id == id);
}

update_ret_type GoodsPromotionRepository::updateById(
    id_type id, const GoodsPromotionDTO &goods_promotion_dto) {
  return _update(goods_promotion_dto, db::goods_promotion{}.id == id);
}

delete_ret_type GoodsPromotionRepository::removeById(id_type id) {
  return _remove(db::goods_promotion{}.id == id);
}

bool GoodsPromotionRepository::existsById(id_type id) {
  return _exists(db::goods_promotion{}.id == id);
}

// 面向业务 CRUD（external）
select_ret_type<GoodsPromotionDTO>
GoodsPromotionRepository::getByGoodsRKId(id_type goods_rk_id) {
  return _select(db::goods_promotion{}.goods_rk_id == goods_rk_id);
}

select_ret_type<GoodsPromotionDTO>
GoodsPromotionRepository::getByPromotionRKId(id_type promotion_rk_id) {
  return _select(db::goods_promotion{}.promotion_rk_id == promotion_rk_id);
}

update_ret_type GoodsPromotionRepository::updateByGoodsRKId(
    id_type goods_rk_id, const GoodsPromotionDTO &goods_promotion_dto) {
  return _update(goods_promotion_dto,
                 db::goods_promotion{}.goods_rk_id == goods_rk_id);
}

delete_ret_type
GoodsPromotionRepository::removeByGoodRKsId(id_type goods_rk_id) {
  return _remove(db::goods_promotion{}.goods_rk_id == goods_rk_id);
}

bool GoodsPromotionRepository::existsByGoodsRKId(id_type goods_rk_id) {
  return _exists(db::goods_promotion{}.goods_rk_id == goods_rk_id);
}

// other
select_ret_type<GoodsPromotionDTO> GoodsPromotionRepository::getAll() {
  return _select(db::goods_promotion{}.id >= 0);
}

select_ret_type<GoodsPromotionDTO>
GoodsPromotionRepository::getByPage(count_type page_size, count_type offset) {
  return _select_from(db::goods_promotion{}.id >= 0, page_size, offset);
}

count_type GoodsPromotionRepository::count() { return _count(); }
