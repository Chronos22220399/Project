#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/warehouse/inventory_check_order_repository.h>
#include <service/warehouse/inventory_check_order_service.h>

using json = nlohmann::json;

ServiceResult InventoryCheckOrderService::create(InventoryCheckOrderDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult InventoryCheckOrderService::updateByOrderId(const std::string &ex_id, InventoryCheckOrderDTO &dto) {
	return {false, "Not implemented yet."};
 }

ServiceResult InventoryCheckOrderService::removeByOrderId(const std::string &ex_id) {
	return {false, "Not implemented yet."};
 }

ServiceResult InventoryCheckOrderService::getByPage(const int page, const int page_size) {
	return {false, "Not implemented yet."};
 }

ServiceResult InventoryCheckOrderService::getAll() {
	return {false, "Not implemented yet."};
 }
