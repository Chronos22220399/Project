#include <repository/goods/goods_category_repository.h>

// CRUD Operations
insert_ret_type
GoodsCategoryRepository::create(const GoodsCategoryDTO &goods_category_dto) {
  return _insert(goods_category_dto);
}
select_ret_type<GoodsCategoryDTO>
GoodsCategoryRepository::get(const std::string &goods_category_name) {
  return _select(db::goods_category{}.goods_category_name ==
                 goods_category_name);
}

update_ret_type
GoodsCategoryRepository::update(const GoodsCategoryDTO &goods_category_dto) {
  return _update(goods_category_dto,
                 db::goods_category{}.id == goods_category_dto.id);
}

delete_ret_type
GoodsCategoryRepository::remove(const std::string &goods_category_id) {
  return _remove(db::goods_category{}.goods_category_id == goods_category_id);
}

// Custom Queries
select_ret_type<GoodsCategoryDTO> GoodsCategoryRepository::getAll() {
  return _select(db::goods_category{}.id >= 0);
}

select_ret_type<GoodsCategoryDTO>
GoodsCategoryRepository::getByPage(count_type page_size, count_type offset) {
  return _select_from(db::goods_category{}.id >= 0, page_size, offset);
}

count_type GoodsCategoryRepository::count() { return _count(); }
