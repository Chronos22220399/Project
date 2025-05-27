#pragma once
#include <crow.h>
#include <string>
#include <model/dto/employee/attendance_record_dto.hpp>

class AttendanceRecordService {
public:
    static ServiceResult create(AttendanceRecordDTO &dto);
static ServiceResult updateByAttendanceRecordId(const std::string &ex_id, AttendanceRecordDTO &dto);
static ServiceResult removeByAttendanceRecordId(const std::string &ex_id);
static ServiceResult getByPage(const int page, const int page_size);
static ServiceResult getAll();
};
