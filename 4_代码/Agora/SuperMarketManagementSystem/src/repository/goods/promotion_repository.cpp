#include <repository/goods/promotion_repository.h>

// 通用 CRUD（internal）
insert_ret_type PromotionRepository::create(const PromotionDTO &promotion_dto) {
  return _insert(promotion_dto);
}

select_ret_type<PromotionDTO> PromotionRepository::getById(id_type id) {
  return _select(db::promotion{}.id == id);
}

update_ret_type
PromotionRepository::updateById(id_type id, const PromotionDTO &promotion_dto) {
  return _update(promotion_dto, db::promotion{}.id == id);
}

delete_ret_type PromotionRepository::removeById(id_type id) {
  return _remove(db::promotion{}.id == id);
}

bool PromotionRepository::existsById(id_type id) {
  return _exists(db::promotion{}.id == id);
}

// 面向业务 CRUD（external）
select_ret_type<PromotionDTO>
PromotionRepository::getByPromotionId(const std::string &promotion_id) {
  return _select(db::promotion{}.promotion_id == promotion_id);
}

update_ret_type
PromotionRepository::updateByPromotionId(const std::string &promotion_id,
                                         const PromotionDTO &promotion_dto) {
  return _update(promotion_dto, db::promotion{}.promotion_id == promotion_id);
}

delete_ret_type
PromotionRepository::removeByPromotionId(const std::string &promotion_id) {
  return _remove(db::promotion{}.promotion_id == promotion_id);
}

bool PromotionRepository::existsByPromotionId(const std::string &promotion_id) {
  return _exists(db::promotion{}.promotion_id == promotion_id);
}

// other
select_ret_type<PromotionDTO> PromotionRepository::getAll() {
  return _select(db::promotion{}.id >= 0);
}

select_ret_type<PromotionDTO>
PromotionRepository::getByPage(count_type page_size, count_type offset) {
  return _select_from(db::promotion{}.id >= 0, page_size, offset);
}

count_type PromotionRepository::count() { return _count(); }
