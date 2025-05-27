#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/employee/attendance_record_repository.h>
#include <service/employee/attendance_record_service.h>

using json = nlohmann::json;

ServiceResult AttendanceRecordService::create(AttendanceRecordDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult AttendanceRecordService::updateByAttendanceRecordId(const std::string &ex_id, AttendanceRecordDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult AttendanceRecordService::removeByAttendanceRecordId(const std::string &ex_id) {
	return {false, "Not implemented yet."};
 }

ServiceResult AttendanceRecordService::getByPage(const int page, const int page_size) {
	return {false, "Not implemented yet."};
 }

ServiceResult AttendanceRecordService::getAll() {
	return {false, "Not implemented yet."};
 }
