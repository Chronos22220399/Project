#include <common/common_utils.hpp>
#include <nlohmann/json.hpp>
#include <repository/goods_repository.h>
#include <service/goods_service.h>

using json = nlohmann::json;

namespace goods {
namespace details {

const std::vector<std::string> required_fields = {
    "goods_name",      "category_id", "supplier_id", "unit_id",
    "shelf_life_days", "barcode",     "image_url",   "description"};

} // namespace details
} // namespace goods

crow::response GoodsService::addGoods(const std::string &body) {
  using namespace goods::details;
  json j;
  try {
    j = json::parse(body);
  } catch (const std::exception &e) {
    return crow::response(400, "Invalid JSON");
  }

  for (const auto &field : required_fields) {
    if (!j.contains(field)) {
      return crow::response(400, "Missing field: " + field);
    }
  }

  bool success = GoodsRepository::insert(GoodsDTO::from_json(j));
  return success ? crow::response(200) : crow::response(500);
}
