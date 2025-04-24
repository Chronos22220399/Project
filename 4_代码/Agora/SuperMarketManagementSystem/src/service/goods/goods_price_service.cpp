#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/goods/goods_price_repository.h>
#include <service/goods/goods_price_service.h>

using json = nlohmann::json;

crow::response GoodsPriceService::add(const std::string &body) {
	return crow::response(200);
 }

crow::response GoodsPriceService::getByPage(const std::string &body) {
	return crow::response(200);
 }

crow::response GoodsPriceService::getAll() {
	return crow::response(200);
 }
