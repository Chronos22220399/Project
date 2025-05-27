#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/supplier/supplier_contract_repository.h>
#include <service/supplier/supplier_contract_service.h>

using json = nlohmann::json;

ServiceResult SupplierContractService::create(SupplierContractDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult SupplierContractService::updateBySupplierContractId(const std::string &ex_id, SupplierContractDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult SupplierContractService::removeBySupplierContractId(const std::string &ex_id) {
	return {false, "Not implemented yet."};
 }

ServiceResult SupplierContractService::getByPage(const int page, const int page_size) {
	return {false, "Not implemented yet."};
 }

ServiceResult SupplierContractService::getAll() {
	return {false, "Not implemented yet."};
 }
