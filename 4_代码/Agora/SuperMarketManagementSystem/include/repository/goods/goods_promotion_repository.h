#pragma once
#include <common/generic_model.hpp>
#include <model/dto/goods/goods_promotion_dto.hpp>

class GoodsPromotionRepository
    : protected model::GenericModel<GoodsPromotionDTO, db::goods_promotion> {
public:
  // 通用 CRUD（internal）
  static insert_ret_type create(const GoodsPromotionDTO &goods_promotion_dto);
  static select_ret_type<GoodsPromotionDTO> getById(id_type id);
  static update_ret_type
  updateById(id_type id, const GoodsPromotionDTO &goods_promotion_dto);
  static delete_ret_type removeById(id_type id);
  static bool existsById(id_type id);

  // 面向业务 CRUD（external）
  static select_ret_type<GoodsPromotionDTO> getByGoodsRKId(id_type goods_rk_id);
  static select_ret_type<GoodsPromotionDTO>
  getByPromotionRKId(id_type promotion_rk_id);
  static update_ret_type
  updateByGoodsRKId(id_type goods_rk_id,
                    const GoodsPromotionDTO &goods_promotion_dto);
  static delete_ret_type removeByGoodRKsId(id_type goods_rk_id);
  static bool existsByGoodsRKId(id_type goods_rk_id);

  // other
  static select_ret_type<GoodsPromotionDTO> getAll();
  static select_ret_type<GoodsPromotionDTO> getByPage(count_type page_size,
                                                      count_type offset);
  static count_type count();
};
