#include <nlohmann/json.hpp>
#include <repository/goods_repository.h>
#include <service/goods_service.h>

using json = nlohmann::json;

crow::response GoodsService::addGoods(const std::string &body) {
  json j = json::parse(body);
  if (!j.contains("name"))
    return crow::response(400, "Missing name");

  bool success = GoodsRepository::insert(j["name"], j["price"]);
  return success ? crow::response(200) : crow::response(500);
}
