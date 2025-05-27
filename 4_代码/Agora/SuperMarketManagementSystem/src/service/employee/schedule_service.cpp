#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/employee/schedule_repository.h>
#include <service/employee/schedule_service.h>

using json = nlohmann::json;

ServiceResult ScheduleService::create(ScheduleDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult ScheduleService::updateByScheduleId(const std::string &ex_id, ScheduleDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult ScheduleService::removeByScheduleId(const std::string &ex_id) {
	return {false, "Not implemented yet."};
 }

ServiceResult ScheduleService::getByPage(const int page, const int page_size) {
	return {false, "Not implemented yet."};
 }

ServiceResult ScheduleService::getAll() {
	return {false, "Not implemented yet."};
 }
