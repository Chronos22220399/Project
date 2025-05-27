#include <repository/employee/payroll_record_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type PayrollRecordRepository::create(const PayrollRecordDTO &payroll_record_dto) {
    return _insert(payroll_record_dto);
};

select_ret_type<PayrollRecordDTO> PayrollRecordRepository::get(const std::string& payroll_record_name) {
  return _select(db::payroll_record{}.payroll_record_name == payroll_record_name);
};

update_ret_type PayrollRecordRepository::update(const PayrollRecordDTO &dto) {
    return _update(dto, db::payroll_record{}.payroll_record_id == dto.payroll_record_id);
};

delete_ret_type PayrollRecordRepository::remove(const std::string& payroll_record_id) {
  return _remove(db::payroll_record{}.payroll_record_id == payroll_record_id);
}

// Custom Queries
select_ret_type<PayrollRecordDTO> PayrollRecordRepository::getAll() {
  return _select(db::payroll_record{}.id >= 0);
}

select_ret_type<PayrollRecordDTO> PayrollRecordRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::payroll_record{}.id >= 0, page_size, offset);
}

count_type PayrollRecordRepository::count() { return _count(); }

// 其他方法实现...
