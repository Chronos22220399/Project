#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/member/points_exchange_record_repository.h>
#include <service/member/points_exchange_record_service.h>

using json = nlohmann::json;

ServiceResult PointsExchangeRecordService::create({} &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult PointsExchangeRecordService::update(const std::string &ex_id, {} &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult PointsExchangeRecordService::remove(const std::string &ex_id) {
	return {false, "Not implemented yet."};
 }

ServiceResult PointsExchangeRecordService::getByPage(const int page, const int page_size) {
	return {false, "Not implemented yet."};
 }

ServiceResult PointsExchangeRecordService::getAll() {
	return {false, "Not implemented yet."};
 }
