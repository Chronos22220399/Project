#pragma once
#include <model/dto/warehouse/inventory_out_dto.hpp>
#include <common/generic_model.hpp>

class InventoryOutRepository : public model::GenericModel<InventoryOutDTO, db::inventory_out> {
public:
    // CRUD Operations
    static insert_ret_type create(const InventoryOutDTO& InventoryOutDTO);
    static select_ret_type<InventoryOutDTO> get(const std::string &inventory_out_name);
    static update_ret_type update(const InventoryOutDTO& inventory_out_dto);
    static delete_ret_type remove(const std::string &inventory_out_id);
    
    // Custom Queries
    static select_ret_type<InventoryOutDTO> get_all();
    static select_ret_type<InventoryOutDTO> get_by_page(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    static select_ret_type<InventoryOutDTO> getByGoodsRkId(id_type goods_rk_id);
    static select_ret_type<InventoryOutDTO> getByWarehouseRkId(id_type warehouse_rk_id);
    static select_ret_type<InventoryOutDTO> getByUnitRkId(id_type unit_rk_id);
};
