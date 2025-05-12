#pragma once
#include <model/dto/warehouse/inventory_in_dto.hpp>
#include <common/generic_model.hpp>

class InventoryInRepository : public model::GenericModel<InventoryInDTO, db::inventory_in> {
public:
    // CRUD Operations
    static insert_ret_type create(const InventoryInDTO& InventoryInDTO);
    static select_ret_type<InventoryInDTO> get(const std::string &inventory_in_name);
    static update_ret_type update(const InventoryInDTO& inventory_in_dto);
    static delete_ret_type remove(const std::string &inventory_in_id);
    
    // Custom Queries
    static select_ret_type<InventoryInDTO> get_all();
    static select_ret_type<InventoryInDTO> get_by_page(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    static select_ret_type<InventoryInDTO> getByGoodsRkId(id_type goods_rk_id);
    static select_ret_type<InventoryInDTO> getByWarehouseRkId(id_type warehouse_rk_id);
    static select_ret_type<InventoryInDTO> getByUnitRkId(id_type unit_rk_id);
};
