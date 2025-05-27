#pragma once
#include <common/generic_model.hpp>
#include <model/dto/supplier/purchase_order_dto.hpp>

class PurchaseOrderRepository
  : public model::GenericModel<PurchaseOrderDTO, db::purchase_order> {
  public:
  // CRUD Operations
  static insert_ret_type create(const PurchaseOrderDTO& PurchaseOrderDTO);
  static select_ret_type<PurchaseOrderDTO>
  getBySupplierRKId(const in_id_type supplier_rk_id);
  static update_ret_type updateById(const in_id_type,
                                    const PurchaseOrderDTO& purchase_order_dto);
  static delete_ret_type removeById(const in_id_type id);

  // Custom Queries
  static select_ret_type<PurchaseOrderDTO> getAll();
  static select_ret_type<PurchaseOrderDTO> getByPage(int page_size, int offset);
  static count_type count();


  // Foreign Key Relations
};
