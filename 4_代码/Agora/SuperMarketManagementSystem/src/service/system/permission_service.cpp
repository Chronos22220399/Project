#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/system/permission_repository.h>
#include <service/system/permission_service.h>

using json = nlohmann::json;

ServiceResult PermissionService::create(PermissionDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult PermissionService::updateByPermissionId(const std::string &ex_id, PermissionDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult PermissionService::removeByPermissionId(const std::string &ex_id) {
	return {false, "Not implemented yet."};
 }

ServiceResult PermissionService::getByPage(const int page, const int page_size) {
	return {false, "Not implemented yet."};
 }

ServiceResult PermissionService::getAll() {
	return {false, "Not implemented yet."};
 }
