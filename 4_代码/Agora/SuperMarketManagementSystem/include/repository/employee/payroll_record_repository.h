#pragma once
#include <model/dto/employee/payroll_record_dto.hpp>
#include <common/generic_model.hpp>

class PayrollRecordRepository : public model::GenericModel<PayrollRecordDTO, db::payroll_record> {
public:
    // CRUD Operations
    static insert_ret_type create(const PayrollRecordDTO& PayrollRecordDTO);
    static select_ret_type<PayrollRecordDTO> get(const std::string &payroll_record_name);
    static update_ret_type updateById(const in_id_type id, const PayrollRecordDTO& payroll_record_dto);
    static delete_ret_type removeById(const in_id_type id);
    
    // Custom Queries
    static select_ret_type<PayrollRecordDTO> getAll();
    static select_ret_type<PayrollRecordDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    
};
