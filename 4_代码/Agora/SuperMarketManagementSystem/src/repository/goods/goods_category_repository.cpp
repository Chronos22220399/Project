#include <repository/goods/goods_category_repository.h>

insert_ret_type
GoodsCategoryRepository::insert(const GoodsCategoryDTO &goods_category_dto) {
  return _insert(goods_category_dto);
}

select_ret_type<GoodsCategoryDTO> GoodsCategoryRepository::getAllCategory() {
  return _select(db::category{}.id >= 0);
}

select_ret_type<GoodsCategoryDTO>
GoodsCategoryRepository::getCategoryByPage(count_type page_size,
                                           count_type offset) {
  return _select_from(db::category{}.id >= 0, page_size, offset);
}

count_type GoodsCategoryRepository::count() { return _count(); }
