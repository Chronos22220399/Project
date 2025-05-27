#pragma once
#include <model/dto/employee/attendance_record_dto.hpp>
#include <common/generic_model.hpp>

class AttendanceRecordRepository : public model::GenericModel<AttendanceRecordDTO, db::attendance_record> {
public:
    // CRUD Operations
    static insert_ret_type create(const AttendanceRecordDTO& AttendanceRecordDTO);
    static select_ret_type<AttendanceRecordDTO> get(const std::string &attendance_record_name);
    static update_ret_type updateById(const in_id_type id, const AttendanceRecordDTO& attendance_record_dto);
    static delete_ret_type removeById(const in_id_type id);
    
    // Custom Queries
    static select_ret_type<AttendanceRecordDTO> getAll();
    static select_ret_type<AttendanceRecordDTO> getByPage(int page_size, int offset);
    static count_type count();
    
    
    // Foreign Key Relations
    
};
