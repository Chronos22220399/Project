#include <common/common_utils.hpp>      
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/common/unit_repository.h>
#include <service/common/unit_service.h>

using json = nlohmann::json;

crow::response UnitService::add(const std::string &body) {
	return crow::response(200);
 }

crow::response UnitService::getByPage(const std::string &body) {
	return crow::response(200);
 }

crow::response UnitService::getAll() {
	return crow::response(200);
 }
