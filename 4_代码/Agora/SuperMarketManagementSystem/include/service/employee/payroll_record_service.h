#pragma once
#include <crow.h>
#include <string>
#include<model/dto/employee/payroll_record_dto.hpp>

class PayrollRecordService {
public:
    static ServiceResult create(PayrollRecordDTO &dto);
static ServiceResult updateByPayrollRecordId(const std::string &ex_id, PayrollRecordDTO &dto);
static ServiceResult removeByPayrollRecordId(const std::string &ex_id);
static ServiceResult getByPage(const int page, const int page_size);
static ServiceResult getAll();
};
