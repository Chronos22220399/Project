#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/supplier/supplier_evaluation_repository.h>
#include <service/supplier/supplier_evaluation_service.h>

using json = nlohmann::json;

ServiceResult SupplierEvaluationService::create(SupplierEvaluationDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult SupplierEvaluationService::updateBySupplierEvaluationId(const std::string &ex_id, SupplierEvaluationDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult SupplierEvaluationService::removeBySupplierEvaluationId(const std::string &ex_id) {
	return {false, "Not implemented yet."};
 }

ServiceResult SupplierEvaluationService::getByPage(const int page, const int page_size) {
	return {false, "Not implemented yet."};
 }

ServiceResult SupplierEvaluationService::getAll() {
	return {false, "Not implemented yet."};
 }
