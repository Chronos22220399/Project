#pragma once
#include <model/dto/sales/sales_return_dto.hpp>
#include <common/generic_model.hpp>

class SalesReturnRepository : public model::GenericModel<SalesReturnDTO, db::sales_return> {
public:
    // CRUD Operations
    static insert_ret_type create(const SalesReturnDTO& SalesReturnDTO);
    static select_ret_type<SalesReturnDTO> get(const std::string &sales_return_name);
    static update_ret_type updateById(const in_id_type id, const SalesReturnDTO& sales_return_dto);
    static delete_ret_type removeById(const in_id_type id);
    
    // Custom Queries
    static select_ret_type<SalesReturnDTO> getAll();
    static select_ret_type<SalesReturnDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    
};
