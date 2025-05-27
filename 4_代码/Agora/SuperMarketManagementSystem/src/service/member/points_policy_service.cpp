#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/member/points_policy_repository.h>
#include <service/member/points_policy_service.h>

using json = nlohmann::json;

ServiceResult PointsPolicyService::create({} &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult PointsPolicyService::update(const std::string &ex_id, {} &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult PointsPolicyService::remove(const std::string &ex_id) {
	return {false, "Not implemented yet."};
 }

ServiceResult PointsPolicyService::getByPage(const int page, const int page_size) {
	return {false, "Not implemented yet."};
 }

ServiceResult PointsPolicyService::getAll() {
	return {false, "Not implemented yet."};
 }
