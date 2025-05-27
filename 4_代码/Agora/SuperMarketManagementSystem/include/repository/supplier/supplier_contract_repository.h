#pragma once
#include <model/dto/supplier/supplier_contract_dto.hpp>
#include <common/generic_model.hpp>

class SupplierContractRepository : public model::GenericModel<SupplierContractDTO, db::supplier_contract> {
public:
    // CRUD Operations
    static insert_ret_type create(const SupplierContractDTO& SupplierContractDTO);
    static select_ret_type<SupplierContractDTO> get(const std::string &supplier_contract_name);
    static update_ret_type update(const SupplierContractDTO& supplier_contract_dto);
    static delete_ret_type remove(const std::string &supplier_contract_id);
    
    // Custom Queries
    static select_ret_type<SupplierContractDTO> getAll();
    static select_ret_type<SupplierContractDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    
};
