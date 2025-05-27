#pragma once
#include <common/generic_model.hpp>
#include <model/dto/supplier/supplier_contract_dto.hpp>

class SupplierContractRepository
  : public model::GenericModel<SupplierContractDTO, db::supplier_contract> {
  public:
  // CRUD Operations
  static insert_ret_type create(const SupplierContractDTO& SupplierContractDTO);
  static select_ret_type<SupplierContractDTO>
  getBySupplierRKId(const in_id_type supplier_rk_id);
  static update_ret_type
  updateById(const in_id_type id,
             const SupplierContractDTO& supplier_contract_dto);
  static delete_ret_type removeById(const in_id_type id);

  // Custom Queries
  static select_ret_type<SupplierContractDTO> getAll();
  static select_ret_type<SupplierContractDTO> getByPage(int page_size,
                                                        int offset);
  static count_type count();


  // Foreign Key Relations
};
