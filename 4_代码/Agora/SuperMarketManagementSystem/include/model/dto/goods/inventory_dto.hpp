#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/global_id_cache.hpp>
#include <common/uni_define.h>

// third_party
#include <nlohmann/json.hpp>

// table
#include <model/db/goods/inventory.h>

// DTO for inventory table
struct InventoryDTO {
  id_type id = 0;
  id_type goods_rk_id = 0;
  id_type warehouse_rk_id = 0;
  id_type quantity = 0;
};

inline void to_json(nlohmann::json &j, const InventoryDTO &inventory_dto) {
  j = nlohmann::json{
      {"goods_id", GlobalIdCache::getInstance().getExternalId(
                       "goods", inventory_dto.goods_rk_id)},
      {"warehouse_id", GlobalIdCache::getInstance().getExternalId(
                           "warehouse", inventory_dto.warehouse_rk_id)},
      {"quantity", inventory_dto.quantity}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<InventoryDTO, db::inventory> {
  static constexpr auto map_members = std::make_tuple(
      std::make_pair(&InventoryDTO::id, &db::inventory::id),
      std::make_pair(&InventoryDTO::goods_rk_id, &db::inventory::goods_rk_id),
      std::make_pair(&InventoryDTO::warehouse_rk_id,
                     &db::inventory::warehouse_rk_id),
      std::make_pair(&InventoryDTO::quantity, &db::inventory::quantity));
};

// mapping
template <typename InventoryRow>
struct ReflectTableRow<InventoryDTO, InventoryRow> {
  static InventoryDTO assign_model(InventoryRow &&row) {
    return InventoryDTO{.id = row.id,
                        .goods_rk_id = row.goods_rk_id,
                        .warehouse_rk_id = row.warehouse_rk_id,
                        .quantity = row.quantity};
  }
};

} // namespace model
