#pragma once
#include <model/dto/warehouse/warehouse_dto.hpp>
#include <common/generic_model.hpp>

class WarehouseRepository : protected model::GenericModel<WarehouseDTO, db::warehouse> {
public:
    // CRUD Operations
    static insert_ret_type create(const WarehouseDTO& WarehouseDTO);
    static select_ret_type<WarehouseDTO> get(id_type id);
    static update_ret_type update(const WarehouseDTO& warehouse_dto);
    static delete_ret_type remove(id_type id);
    
    // Custom Queries
    static select_ret_type<WarehouseDTO> getAll();
    static select_ret_type<WarehouseDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    // Foreign Key Relations
    
};
