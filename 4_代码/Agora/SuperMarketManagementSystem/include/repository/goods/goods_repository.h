#pragma once
#include <model/dto/goods/goods_dto.hpp>

class GoodsRepository : protected model::GenericModel<GoodsDTO, db::goods> {
public:
  static insert_ret_type create(const GoodsDTO &goods_dto);
  static select_ret_type<GoodsDTO> getAll();
  static select_ret_type<GoodsDTO> getByPage(count_type page_size,
                                             count_type offset);
  static count_type count();
};
