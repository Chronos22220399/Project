#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/supplier/supplier_repository.h>
#include <service/supplier/supplier_service.h>

using json = nlohmann::json;

ServiceResult SupplierService::create(SupplierDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult SupplierService::updateBySupplierId(const std::string &ex_id, SupplierDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult SupplierService::removeBySupplierId(const std::string &ex_id) {
	return {false, "Not implemented yet."};
 }

ServiceResult SupplierService::getByPage(const int page, const int page_size) {
	return {false, "Not implemented yet."};
 }

ServiceResult SupplierService::getAll() {
	return {false, "Not implemented yet."};
 }
