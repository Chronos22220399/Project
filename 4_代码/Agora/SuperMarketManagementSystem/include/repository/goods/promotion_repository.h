#pragma once
#include <common/generic_model.hpp>
#include <model/dto/goods/promotion_dto.hpp>

class PromotionRepository
    : public model::GenericModel<PromotionDTO, db::promotion> {
public:
  // CRUD Operations
  static insert_ret_type create(const PromotionDTO &PromotionDTO);
  static select_ret_type<PromotionDTO> get(id_type id);
  static update_ret_type update(const PromotionDTO &promotion_dto);
  static delete_ret_type remove(id_type id);

  // Custom Queries
  static select_ret_type<PromotionDTO> getAll();
  static select_ret_type<PromotionDTO> getByPage(int page_size, int offset);
  static count_type count();

  // Foreign Key Relations
};
