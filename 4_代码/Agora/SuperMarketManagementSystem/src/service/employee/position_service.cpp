#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/employee/position_repository.h>
#include <service/employee/position_service.h>

using json = nlohmann::json;

ServiceResult PositionService::create(PositionDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult PositionService::updateByPositionId(const std::string &ex_id,PositionDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult PositionService::removeByPositionId(const std::string &ex_id) {
	return {false, "Not implemented yet."};
 }

ServiceResult PositionService::getByPage(const int page, const int page_size) {
	return {false, "Not implemented yet."};
 }

ServiceResult PositionService::getAll() {
	return {false, "Not implemented yet."};
 }
