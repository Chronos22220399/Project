#pragma once
#include <model/dto/warehouse/inventory_check_order_dto.hpp>
#include <common/generic_model.hpp>

class InventoryCheckOrderRepository : public model::GenericModel<InventoryCheckOrderDTO, db::inventory_check_order> {
public:
    // CRUD Operations
    static insert_ret_type create(const InventoryCheckOrderDTO& InventoryCheckOrderDTO);
    static select_ret_type<InventoryCheckOrderDTO> get(const std::string &inventory_check_order_name);
    static update_ret_type update(const InventoryCheckOrderDTO& inventory_check_order_dto);
    static delete_ret_type remove(const std::string &inventory_check_order_id);
    
    // Custom Queries
    static select_ret_type<InventoryCheckOrderDTO> getAll();
    static select_ret_type<InventoryCheckOrderDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    
};
