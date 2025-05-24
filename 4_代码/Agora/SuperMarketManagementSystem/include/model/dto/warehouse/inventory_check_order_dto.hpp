#pragma once
#include <common/cache_func_getter.h>
#include <common/generic_model.hpp>
#include <model/db/warehouse/inventory_check_order.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for inventory_check_order table
struct InventoryCheckOrderDTO : public CacheFuncGetter {
  inline static const std::vector<std::string> required_fields = {
    "warehouse_id",  //
    "created_by",    //
    "remark"         //
  };
  inline static const std::vector<std::string> status_domain = {
    "draft",      // 草稿
    "submitted",  // 已提交
    "audited"     // 已审核
  };

  in_id_type id = 0;
  ex_id_type order_id = "";
  in_id_type warehouse_rk_id = 0;
  datetime_type created_at = {};
  in_id_type created_by = 0;
  in_id_type audited_by = 0;
  datetime_type audited_at = {};
  status_type status = "";
  remark_type remark = "";

  // JSON serialization/deserialization
  static InventoryCheckOrderDTO from_json(const nlohmann::json& j)
  {
    try {
      return InventoryCheckOrderDTO{
        .warehouse_rk_id =
          getInternalId("warehouse", j.at("warehouse_id").get<ex_id_type>()),
        .created_at =
          utils::string_to_time(j.at("created_at").get<std::string>()),
        .created_by =
          getInternalId("employee", j.at("created_by").get<ex_id_type>()),
        .status = j.at("status").get<std::string>(),
        .remark = j.at("remark").get<std::string>()};
    }
    catch (const std::exception& e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json& j, const InventoryCheckOrderDTO& dto)
{
  j = nlohmann::json{
    {"order_id", dto.order_id},
    {"warehouse_id", dto.getExternalId("warehouse", dto.warehouse_rk_id)},
    {"created_at", utils::time_to_string(dto.created_at)},
    {"created_by", dto.created_by},
    {"audited_by", dto.audited_by},
    {"audited_at", utils::time_to_string(dto.audited_at)},
    {"status", dto.status},
    {"status", dto.status},
    {"remark", dto.remark}};
}

// ORM mapping
namespace model {
template <>
struct ReflectTable<InventoryCheckOrderDTO, db::inventory_check_order> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&InventoryCheckOrderDTO::id, &db::inventory_check_order::id),
    std::make_pair(&InventoryCheckOrderDTO::order_id,
                   &db::inventory_check_order::order_id),
    std::make_pair(&InventoryCheckOrderDTO::warehouse_rk_id,
                   &db::inventory_check_order::warehouse_rk_id),
    std::make_pair(&InventoryCheckOrderDTO::created_at,
                   &db::inventory_check_order::created_at),
    std::make_pair(&InventoryCheckOrderDTO::created_by,
                   &db::inventory_check_order::created_by),
    std::make_pair(&InventoryCheckOrderDTO::audited_by,
                   &db::inventory_check_order::audited_by),
    std::make_pair(&InventoryCheckOrderDTO::audited_at,
                   &db::inventory_check_order::audited_at),
    std::make_pair(&InventoryCheckOrderDTO::status,
                   &db::inventory_check_order::status),
    std::make_pair(&InventoryCheckOrderDTO::remark,
                   &db::inventory_check_order::remark));
};

// mapping
template <typename Inventory_check_orderRow>
struct ReflectTableRow<InventoryCheckOrderDTO, Inventory_check_orderRow> {
  static InventoryCheckOrderDTO assign_model(Inventory_check_orderRow&& row)
  {
    return InventoryCheckOrderDTO{.id = row.id,
                                  .order_id = row.order_id,
                                  .warehouse_rk_id = row.warehouse_rk_id,
                                  .created_at = row.created_at,
                                  .created_by = row.created_by,
                                  .audited_by = row.audited_by,
                                  .audited_at = row.audited_at,
                                  .status = row.status,
                                  .remark = row.remark};
  }
};
}  // namespace model
