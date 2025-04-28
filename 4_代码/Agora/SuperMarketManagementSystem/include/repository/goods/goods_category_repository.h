#pragma once
#include <model/dto/goods/goods_category_dto.hpp>

class GoodsCategoryRepository
    : protected model::GenericModel<GoodsCategoryDTO, db::goods_category> {
public:
  // CRUD Operations
  static insert_ret_type create(const GoodsCategoryDTO &goods_category_dto);
  static select_ret_type<GoodsCategoryDTO>
  get(const std::string &goods_category_name);
  static update_ret_type update(const GoodsCategoryDTO &goods_category_dto);
  static delete_ret_type remove(const std::string &goods_category_id);

  // Custom Queries
  static select_ret_type<GoodsCategoryDTO> getAll();
  static select_ret_type<GoodsCategoryDTO> getByPage(count_type page_size,
                                                     count_type offset);
  static count_type count();
};
