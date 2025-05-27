#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/sales/sales_return_repository.h>
#include <service/sales/sales_return_service.h>

using json = nlohmann::json;

ServiceResult SalesReturnService::create(SalesReturnDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult SalesReturnService::updateBySalesReturnId(const std::string &ex_id, SalesReturnDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult SalesReturnService::removeBySalesReturnId(const std::string &ex_id) {
	return {false, "Not implemented yet."};
 }

ServiceResult SalesReturnService::getByPage(const int page, const int page_size) {
	return {false, "Not implemented yet."};
 }

ServiceResult SalesReturnService::getAll() {
	return {false, "Not implemented yet."};
 }
