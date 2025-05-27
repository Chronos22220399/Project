#include <repository/employee/employee_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type EmployeeRepository::create(const EmployeeDTO &employee_dto) {
    return _insert(employee_dto);
};

select_ret_type<EmployeeDTO> EmployeeRepository::get(const std::string& employee_name) {
  return _select(db::employee{}.employee_name == employee_name);
};

update_ret_type EmployeeRepository::update(const EmployeeDTO &dto) {
    return _update(dto, db::employee{}.employee_id == dto.employee_id);
};

delete_ret_type EmployeeRepository::remove(const std::string& employee_id) {
  return _remove(db::employee{}.employee_id == employee_id);
}

// Custom Queries
select_ret_type<EmployeeDTO> EmployeeRepository::getAll() {
  return _select(db::employee{}.id >= 0);
}

select_ret_type<EmployeeDTO> EmployeeRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::employee{}.id >= 0, page_size, offset);
}

count_type EmployeeRepository::count() { return _count(); }

// 其他方法实现...
