#pragma once
#include <model/dto/goods/goods_category_dto.hpp>

class GoodsCategoryRepository
    : protected model::GenericModel<GoodsCategoryDTO, db::goods_category> {
public:
  // 通用 CRUD（internal）
  static insert_ret_type create(const GoodsCategoryDTO &goods_category_dto);
  static select_ret_type<GoodsCategoryDTO> getById(id_type id);
  static update_ret_type updateById(id_type id,
                                    const GoodsCategoryDTO &goods_category_dto);
  static delete_ret_type removeById(id_type id);
  static bool existsById(id_type id);

  // 面向业务 CRUD（external）
  static select_ret_type<GoodsCategoryDTO>
  getByGoodsCategoryId(const std::string &goods_category_id);
  static select_ret_type<GoodsCategoryDTO>
  getByName(const std::string &goods_category_name);
  static update_ret_type
  updateByGoodsCategoryId(const std::string &goods_category_id,
                          const GoodsCategoryDTO &goods_category_dto);
  static delete_ret_type
  removeByGoodsCategoryId(const std::string &goods_category_id);
  static bool existsByGoodsCategoryId(const std::string &goods_category_id);

  // other
  static select_ret_type<GoodsCategoryDTO> getAll();
  static select_ret_type<GoodsCategoryDTO> getByPage(count_type page_size,
                                                     count_type offset);
  static count_type count();
};
