#pragma once
#include <crow.h>
#include <string>
#include <model/dto/employee/employee_dto.hpp>

class EmployeeService {
public:
    static ServiceResult create(EmployeeDTO &dto);
static ServiceResult updateByEmployeeId(const std::string &ex_id, EmployeeDTO &dto);
static ServiceResult removeByEmployeeId(const std::string &ex_id);
static ServiceResult getByPage(const int page, const int page_size);
static ServiceResult getAll();
};
