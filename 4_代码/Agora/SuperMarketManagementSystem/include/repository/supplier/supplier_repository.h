#pragma once
#include <model/dto/supplier/supplier_dto.hpp>
#include <common/generic_model.hpp>

class SupplierRepository : protected model::GenericModel<SupplierDTO, db::supplier> {
public:
    // CRUD Operations
    static insert_ret_type create(const SupplierDTO& dto);
    static select_ret_type<SupplierDTO> get(id_type id);
    static update_ret_type update(const SupplierDTO& dto);
    static delete_ret_type remove(id_type id);
    
    // Custom Queries
    static select_ret_type<SupplierDTO> getAll();
    static select_ret_type<SupplierDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    // Foreign Key Relations
    
};
