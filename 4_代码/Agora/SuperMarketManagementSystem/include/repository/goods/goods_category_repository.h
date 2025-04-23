#pragma once
#include <model/dto/goods/goods_category_dto.hpp>

class GoodsCategoryRepository
    : protected model::GenericModel<GoodsCategoryDTO, db::goods_category> {
public:
  static insert_ret_type insert(const GoodsCategoryDTO &goods_category_dto);

  static select_ret_type<GoodsCategoryDTO> getAllCategory();

  static select_ret_type<GoodsCategoryDTO>
  getCategoryByPage(count_type page_size, count_type offset);

  static count_type count();
};
