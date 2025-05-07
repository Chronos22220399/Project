#pragma once
#include <common/generic_model.hpp>
#include <model/dto/goods/goods_price_dto.hpp>

class GoodsPriceRepository
    : protected model::GenericModel<GoodsPriceDTO, db::goods_price> {
public:
  // 通用 CRUD（internal）
  static insert_ret_type create(const GoodsPriceDTO &goods_price_dto);
  static select_ret_type<GoodsPriceDTO> getById(in_id_type id);
  static update_ret_type updateById(in_id_type id,
                                    const GoodsPriceDTO &goods_price_dto);
  static delete_ret_type removeById(in_id_type id);
  static bool existsById(in_id_type id);

  // 面向业务 CRUD（external）
  static select_ret_type<GoodsPriceDTO> getByGoodsRKId(in_id_type goods_rk_id);
  static update_ret_type
  updateByGoodsRKId(in_id_type goods_rk_id,
                    const GoodsPriceDTO &goods_price_dto);
  static delete_ret_type removeByGoodsRKId(in_id_type goods_rk_id);
  static bool existsByGoodsRKId(in_id_type goods_rk_id);

  // other
  static select_ret_type<GoodsPriceDTO> getAll();
  static select_ret_type<GoodsPriceDTO> getByPage(count_type page_size,
                                                  count_type offset);
  static count_type count();
};
