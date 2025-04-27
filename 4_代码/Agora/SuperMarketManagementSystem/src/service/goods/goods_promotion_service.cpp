#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/goods/goods_promotion_repository.h>
#include <service/goods/goods_promotion_service.h>

using json = nlohmann::json;

crow::response GoodsPromotionService::add(const std::string &body) {
	return crow::response(501, "Not implemented yet.");
 }

crow::response GoodsPromotionService::getByPage(const std::string &body) {
	return crow::response(501, "Not implemented yet.");
 }

crow::response GoodsPromotionService::getAll() {
	return crow::response(501, "Not implemented yet.");
 }
