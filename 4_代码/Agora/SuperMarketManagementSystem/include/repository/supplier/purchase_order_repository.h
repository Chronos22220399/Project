#pragma once
#include <model/dto/supplier/purchase_order_dto.hpp>
#include <common/generic_model.hpp>

class PurchaseOrderRepository : public model::GenericModel<PurchaseOrderDTO, db::purchase_order> {
public:
    // CRUD Operations
    static insert_ret_type create(const PurchaseOrderDTO& PurchaseOrderDTO);
    static select_ret_type<PurchaseOrderDTO> get(const std::string &purchase_order_name);
    static update_ret_type update(const PurchaseOrderDTO& purchase_order_dto);
    static delete_ret_type remove(const std::string &purchase_order_id);
    
    // Custom Queries
    static select_ret_type<PurchaseOrderDTO> getAll();
    static select_ret_type<PurchaseOrderDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    
};
