#include <repository/goods/goods_promotion_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type GoodsPromotionRepository::create(const GoodsPromotionDTO &goods_promotion_dto) {
    return _insert(goods_promotion_dto);
};

select_ret_type<GoodsPromotionDTO> GoodsPromotionRepository::get(id_type id) {
  return _select(db::goods_promotion{}.id == id);
};

update_ret_type GoodsPromotionRepository::update(const GoodsPromotionDTO &dto) {
    return _update(dto, db::goods_promotion{}.id == dto.id);
};

delete_ret_type GoodsPromotionRepository::remove(id_type id) {
  return _remove(db::goods_promotion{}.id == id);
}

// Custom Queries
select_ret_type<GoodsPromotionDTO> GoodsPromotionRepository::getAll() {
  return _select(db::goods_promotion{}.id >= 0);
}

select_ret_type<GoodsPromotionDTO> GoodsPromotionRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::goods_promotion{}.id >= 0, page_size, offset);
}

count_type GoodsPromotionRepository::count() { return _count(); }

// 其他方法实现...
