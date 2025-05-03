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

id_type PromotionRepository::getInternalId(const std::string &promotion_id) {
  auto result = utils::DataBaseHelper::execute<id_type>(
      [&promotion_id](const utils::pooled_conn_ptr_type &conn_) {
        db::promotion promotion{};
        auto rows =
            (*conn_)(select(promotion.id)
                         .from(promotion)
                         .where(promotion.promotion_id == promotion_id));
        return rows.empty() ? 0 : rows.front().id;
      });
  return result;
}

// 获取 external id 用于缓存逆向映射
std::string PromotionRepository::getExternalId(id_type id) {
  auto result = utils::DataBaseHelper::execute<std::string>(
      [id](const utils::pooled_conn_ptr_type &conn_) {
        db::promotion promotion{};
        auto rows = (*conn_)(select(promotion.promotion_id)
                                 .from(promotion)
                                 .where(promotion.id == id));
        return rows.empty() ? std::string() : rows.front().promotion_id;
      });
  return result;
}
