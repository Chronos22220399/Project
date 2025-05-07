#pragma once
#include <common/generic_model.hpp>
#include <model/dto/goods/promotion_dto.hpp>

class PromotionRepository
    : public model::GenericModel<PromotionDTO, db::promotion> {
public:
  // 通用 CRUD（internal）
  static insert_ret_type create(const PromotionDTO &promotion_dto);
  static select_ret_type<PromotionDTO> getById(in_id_type id);
  static update_ret_type updateById(in_id_type id,
                                    const PromotionDTO &promotion_dto);
  static delete_ret_type removeById(in_id_type id);
  static bool existsById(in_id_type id);

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

  // 获取 internal id 用于缓存正向映射
  static in_id_type getInternalId(const std::string &promotion_id);
  // 获取 external id 用于缓存逆向映射
  static std::string getExternalId(in_id_type id);
};
