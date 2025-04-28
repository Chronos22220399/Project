#pragma once
#include <common/generic_model.hpp>
#include <model/dto/goods/promotion_dto.hpp>

class PromotionRepository
    : public model::GenericModel<PromotionDTO, db::promotion> {
public:
  // 通用 CRUD（internal）
  static insert_ret_type create(const PromotionDTO &promotion_dto);
  static select_ret_type<PromotionDTO> getById(id_type id);
  static update_ret_type updateById(id_type id,
                                    const PromotionDTO &promotion_dto);
  static delete_ret_type removeById(id_type id);
  static bool existsById(id_type id);

  // 面向业务 CRUD（external）
  static select_ret_type<PromotionDTO>
  getByPromotionId(const std::string &promotion_id);
  static update_ret_type updateByPromotionId(const std::string &promotion_id,
                                             const PromotionDTO &promotion_dto);
  static delete_ret_type removeByPromotionId(const std::string &promotion_id);
  static bool existsByPromotionId(const std::string &promotion_id);

  // other
  static select_ret_type<PromotionDTO> getAll();
  static select_ret_type<PromotionDTO> getByPage(count_type page_size,
                                                 count_type offset);
  static count_type count();
};
