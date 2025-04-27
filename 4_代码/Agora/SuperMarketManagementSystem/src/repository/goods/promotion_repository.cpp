#include <repository/goods/promotion_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type PromotionRepository::create(const PromotionDTO &promotion_dto) {
  return _insert(promotion_dto);
};

select_ret_type<PromotionDTO> PromotionRepository::get(id_type id) {
  return _select(db::promotion{}.id == id);
};

update_ret_type PromotionRepository::update(const PromotionDTO &dto) {
  return _update(dto, db::promotion{}.id == dto.id);
};

delete_ret_type PromotionRepository::remove(id_type id) {
  return _remove(db::promotion{}.id == id);
}

// Custom Queries
select_ret_type<PromotionDTO> PromotionRepository::getAll() {
  return _select(db::promotion{}.id >= 0);
}

select_ret_type<PromotionDTO> PromotionRepository::getByPage(int page_size,
                                                             int offset) {
  return _select_from(db::promotion{}.id >= 0, page_size, offset);
}

count_type PromotionRepository::count() { return _count(); }

// 其他方法实现...
