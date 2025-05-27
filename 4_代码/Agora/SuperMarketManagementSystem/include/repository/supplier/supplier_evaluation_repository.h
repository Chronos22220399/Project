#pragma once
#include <common/generic_model.hpp>
#include <model/dto/supplier/supplier_evaluation_dto.hpp>

class SupplierEvaluationRepository
  : public model::GenericModel<SupplierEvaluationDTO, db::supplier_evaluation> {
  public:
  // CRUD Operations
  static insert_ret_type
  create(const SupplierEvaluationDTO& SupplierEvaluationDTO);
  static select_ret_type<SupplierEvaluationDTO>
  getBySupplierRKId(const in_id_type supplier_rk_id);
  static update_ret_type
  updateById(const in_id_type id,
             const SupplierEvaluationDTO& supplier_evaluation_dto);
  static delete_ret_type removeById(const in_id_type id);

  // Custom Queries
  static select_ret_type<SupplierEvaluationDTO> getAll();
  static select_ret_type<SupplierEvaluationDTO> getByPage(int page_size,
                                                          int offset);
  static count_type count();


  // Foreign Key Relations
};
