#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/warehouse/stock_in_repository.h>
#include <service/warehouse/stock_in_service.h>

using json = nlohmann::json;

crow::response StockInService::create({} &dto) {
	return crow::response(501, "Not implemented yet.");
 }

crow::response StockInService::update(const std::string &ex_id, {} &dto) {
	return crow::response(501, "Not implemented yet.");
 }

crow::response StockInService::remove(const std::string &ex_id) {
	return crow::response(501, "Not implemented yet.");
 }

crow::response StockInService::getByPage(const int page, const int page_size) {
	return crow::response(501, "Not implemented yet.");
 }

crow::response StockInService::getAll() {
	return crow::response(501, "Not implemented yet.");
 }
