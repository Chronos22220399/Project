#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/global_id_cache.hpp>
#include <common/uni_define.h>
#include <model/db/warehouse/inventory_alert.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for inventory_alert table
struct InventoryAlertDTO {
  in_id_type id = 0;
  in_id_type goods_rk_id = 0;
  quantity_type lower_bound = 0;

  // JSON serialization/deserialization
  static InventoryAlertDTO from_json(const nlohmann::json &j) {
    auto &cache = GlobalIdCache::getInstance();
    try {
      return InventoryAlertDTO{
          .goods_rk_id = cache.getInternalId(
              "inventory_alert", j.at("goods_id").get<ex_id_type>()),
          .lower_bound = j.at("lower_bound").get<quantity_type>(),
      };
    } catch (const std::exception &e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json &j,
                    const InventoryAlertDTO &inventory_alert_dto) {
  auto &cache = GlobalIdCache::getInstance();
  j = nlohmann::json{
      {"goods_id",
       cache.getExternalId("inventory_alert", inventory_alert_dto.goods_rk_id)},
      {"lower_bound", inventory_alert_dto.lower_bound}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<InventoryAlertDTO, db::inventory_alert> {
  static constexpr auto map_members = std::make_tuple(
      std::make_pair(&InventoryAlertDTO::id, &db::inventory_alert::id),
      std::make_pair(&InventoryAlertDTO::goods_rk_id,
                     &db::inventory_alert::goods_rk_id),
      std::make_pair(&InventoryAlertDTO::lower_bound,
                     &db::inventory_alert::lower_bound));
};

// mapping
template <typename Inventory_alertRow>
struct ReflectTableRow<InventoryAlertDTO, Inventory_alertRow> {
  static InventoryAlertDTO assign_model(Inventory_alertRow &&row) {
    return InventoryAlertDTO{.id = row.id,
                             .goods_rk_id = row.goods_rk_id,
                             .lower_bound = row.lower_bound};
  }
};
} // namespace model
