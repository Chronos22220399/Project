#pragma once
#include <model/dto/warehouse/inventory_check_dto.hpp>
#include <common/generic_model.hpp>

class InventoryCheckRepository : public model::GenericModel<InventoryCheckDTO, db::inventory_check> {
public:
    // CRUD Operations
    static insert_ret_type create(const InventoryCheckDTO& InventoryCheckDTO);
    static select_ret_type<InventoryCheckDTO> get(const std::string &inventory_check_name);
    static update_ret_type update(const InventoryCheckDTO& inventory_check_dto);
    static delete_ret_type remove(const std::string &inventory_check_id);
    
    // Custom Queries
    static select_ret_type<InventoryCheckDTO> get_all();
    static select_ret_type<InventoryCheckDTO> get_by_page(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    static select_ret_type<InventoryCheckDTO> getByGoodsRkId(id_type goods_rk_id);
    static select_ret_type<InventoryCheckDTO> getByWarehouseRkId(id_type warehouse_rk_id);
};
