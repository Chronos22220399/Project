#include <repository/employee/attendance_record_repository.h>

using namespace model;

// CRUD Operations
insert_ret_type AttendanceRecordRepository::create(const AttendanceRecordDTO &attendance_record_dto) {
    return _insert(attendance_record_dto);
};

select_ret_type<AttendanceRecordDTO> AttendanceRecordRepository::get(const std::string& attendance_record_name) {
  return _select(db::attendance_record{}.attendance_record_name == attendance_record_name);
};

update_ret_type AttendanceRecordRepository::update(const AttendanceRecordDTO &dto) {
    return _update(dto, db::attendance_record{}.attendance_record_id == dto.attendance_record_id);
};

delete_ret_type AttendanceRecordRepository::remove(const std::string& attendance_record_id) {
  return _remove(db::attendance_record{}.attendance_record_id == attendance_record_id);
}

// Custom Queries
select_ret_type<AttendanceRecordDTO> AttendanceRecordRepository::getAll() {
  return _select(db::attendance_record{}.id >= 0);
}

select_ret_type<AttendanceRecordDTO> AttendanceRecordRepository::getByPage(int page_size,
                                                           int offset) {
  return _select_from(db::attendance_record{}.id >= 0, page_size, offset);
}

count_type AttendanceRecordRepository::count() { return _count(); }

// 其他方法实现...
