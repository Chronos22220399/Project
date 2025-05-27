#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/employee/payroll_record_repository.h>
#include <service/employee/payroll_record_service.h>

using json = nlohmann::json;

ServiceResult PayrollRecordService::create(PayrollRecordDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult PayrollRecordService::updateByPayrollRecordId(const std::string &ex_id, PayrollRecordDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult PayrollRecordService::removeByPayrollRecordId(const std::string &ex_id) {
	return {false, "Not implemented yet."};
 }

ServiceResult PayrollRecordService::getByPage(const int page, const int page_size) {
	return {false, "Not implemented yet."};
 }

ServiceResult PayrollRecordService::getAll() {
	return {false, "Not implemented yet."};
 }
