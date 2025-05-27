#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/member/member_purchase_record_repository.h>
#include <service/member/member_purchase_record_service.h>

using json = nlohmann::json;

ServiceResult MemberPurchaseRecordService::create({} &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult MemberPurchaseRecordService::update(const std::string &ex_id, {} &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult MemberPurchaseRecordService::remove(const std::string &ex_id) {
	return {false, "Not implemented yet."};
 }

ServiceResult MemberPurchaseRecordService::getByPage(const int page, const int page_size) {
	return {false, "Not implemented yet."};
 }

ServiceResult MemberPurchaseRecordService::getAll() {
	return {false, "Not implemented yet."};
 }
