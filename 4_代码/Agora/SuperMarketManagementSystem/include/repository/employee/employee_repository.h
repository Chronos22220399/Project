#pragma once
#include <model/dto/employee/employee_dto.hpp>
#include <common/generic_model.hpp>

class EmployeeRepository : public model::GenericModel<EmployeeDTO, db::employee> {
public:
    // CRUD Operations
    static insert_ret_type create(const EmployeeDTO& EmployeeDTO);
    static select_ret_type<EmployeeDTO> get(const std::string &employee_name);
    static update_ret_type updateById(const in_id_type id, const EmployeeDTO& employee_dto);
    static delete_ret_type removeById(const in_id_type id);
    
    // Custom Queries
    static select_ret_type<EmployeeDTO> getAll();
    static select_ret_type<EmployeeDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    static select_ret_type<EmployeeDTO> getByPositionRkId(in_id_type position_rk_id);
};
