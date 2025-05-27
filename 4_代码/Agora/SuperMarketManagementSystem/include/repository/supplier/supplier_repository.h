#pragma once
#include <model/dto/supplier/supplier_dto.hpp>
#include <common/generic_model.hpp>

class SupplierRepository : public model::GenericModel<SupplierDTO, db::supplier> {
public:
    // CRUD Operations
    static insert_ret_type create(const SupplierDTO& SupplierDTO);
    static select_ret_type<SupplierDTO> get(const std::string &supplier_name);
    static update_ret_type update(const SupplierDTO& supplier_dto);
    static delete_ret_type remove(const std::string &supplier_id);
    
    // Custom Queries
    static select_ret_type<SupplierDTO> getAll();
    static select_ret_type<SupplierDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    
};
