#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/supplier/purchase_order_repository.h>
#include <service/supplier/purchase_order_service.h>

using json = nlohmann::json;

ServiceResult PurchaseOrderService::create(PurchaseOrderDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult PurchaseOrderService::updateByPurchaseOrderId(const std::string &ex_id, PurchaseOrderDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult PurchaseOrderService::removeByPurchaseOrderId(const std::string &ex_id) {
	return {false, "Not implemented yet."};
 }

ServiceResult PurchaseOrderService::getByPage(const int page, const int page_size) {
	return {false, "Not implemented yet."};
 }

ServiceResult PurchaseOrderService::getAll() {
	return {false, "Not implemented yet."};
 }
