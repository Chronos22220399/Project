#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/warehouse/stock_out_repository.h>
#include <service/warehouse/stock_out_service.h>

using json = nlohmann::json;

ServiceResult StockOutService::create({} &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult StockOutService::update(const std::string &ex_id, {} &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult StockOutService::remove(const std::string &ex_id) {
	return {false, "Not implemented yet."};
 }

ServiceResult StockOutService::getByPage(const int page, const int page_size) {
	return {false, "Not implemented yet."};
 }

ServiceResult StockOutService::getAll() {
	return {false, "Not implemented yet."};
 }
