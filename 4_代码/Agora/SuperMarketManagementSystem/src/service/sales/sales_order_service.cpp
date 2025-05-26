#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/sales/sales_order_repository.h>
#include <service/sales/sales_order_service.h>

using json = nlohmann::json;

ServiceResult SalesOrderService::create({} &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult SalesOrderService::update(const std::string &ex_id, {} &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult SalesOrderService::remove(const std::string &ex_id) {
	return {false, "Not implemented yet."};
 }

ServiceResult SalesOrderService::getByPage(const int page, const int page_size) {
	return {false, "Not implemented yet."};
 }

ServiceResult SalesOrderService::getAll() {
	return {false, "Not implemented yet."};
 }
