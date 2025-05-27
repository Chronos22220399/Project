#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/system/system_setting_repository.h>
#include <service/system/system_setting_service.h>

using json = nlohmann::json;

ServiceResult SystemSettingService::create(SystemSettingDTO &dto) {
	return {false, "Not implemented yet."};
 }

// ServiceResult SystemSettingService::update(const std::string &ex_id, {} &dto) {
// 	return {false, "Not implemented yet."};
//  }
//
// ServiceResult SystemSettingService::remove(const std::string &ex_id) {
// 	return {false, "Not implemented yet."};
//  }

ServiceResult SystemSettingService::getByPage(const int page, const int page_size) {
	return {false, "Not implemented yet."};
 }

ServiceResult SystemSettingService::getAll() {
	return {false, "Not implemented yet."};
 }
