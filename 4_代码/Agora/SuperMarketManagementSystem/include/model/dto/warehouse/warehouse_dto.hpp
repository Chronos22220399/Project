#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/global_id_cache.hpp>
#include <common/uni_define.h>
#include <model/db/warehouse/warehouse.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for warehouse table

namespace warehouse::warehouse {
static const std::vector<std::string> status_domain = {"active", "inactive",
                                                       "maintenance", "closed"};
};

struct WarehouseDTO {
  in_id_type id = 0;
  ex_id_type warehouse_id = "";
  name_type warehouse_name = "";
  address_type location = "";
  slot_mount_type capacity = 0.0;
  slot_mount_type available_capacity = 0.0;
  in_id_type manager_rk_id;
  phone_type phone = "";
  datetime_type created_at;
  status_type status;
  remark_type remark;

  // JSON serialization/deserialization
  static WarehouseDTO from_json(const nlohmann::json& j)
  {
    auto& cache = GlobalIdCache::getInstance();
    try {
      return WarehouseDTO{
        .warehouse_id = j.at("warehouse_id").get<ex_id_type>(),
        .warehouse_name = j.at("warehouse_name").get<std::string>(),
        .location = j.at("location").get<std::string>(),
        .capacity = j.at("capacity").get<slot_mount_type>(),
        .available_capacity = j.at("available_capacity").get<slot_mount_type>(),
        .manager_rk_id =
          cache.getInternalId("employee", j.at("manager_id").get<ex_id_type>()),
        .phone = j.at("phone").get<std::string>(),
        .created_at =
          utils::string_to_time(j.at("created_at").get<std::string>()),
        .status = j.at("status").get<status_type>(),
        .remark = j.at("remark").get<remark_type>()};
    }
    catch (const std::exception& e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json& j, const WarehouseDTO& warehouse_dto)
{
  auto& cache = GlobalIdCache::getInstance();
  j = nlohmann::json{
    {"warehouse_id", warehouse_dto.warehouse_id},
    {"warehouse_name", warehouse_dto.warehouse_name},
    {"location", warehouse_dto.location},
    {"capacity", warehouse_dto.capacity},
    {"available_capacity", warehouse_dto.available_capacity},
    {"manager_id",
     cache.getExternalId("employee", warehouse_dto.manager_rk_id)},
    {"phone", warehouse_dto.phone},
    {"created_at", utils::time_to_string(warehouse_dto.created_at)},
    {"status", warehouse_dto.status},
    {"remark", warehouse_dto.remark}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<WarehouseDTO, db::warehouse> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&WarehouseDTO::id, &db::warehouse::id),
    std::make_pair(&WarehouseDTO::warehouse_id, &db::warehouse::warehouse_id),
    std::make_pair(&WarehouseDTO::warehouse_name,
                   &db::warehouse::warehouse_name),
    std::make_pair(&WarehouseDTO::location, &db::warehouse::location),
    std::make_pair(&WarehouseDTO::capacity, &db::warehouse::capacity),
    std::make_pair(&WarehouseDTO::available_capacity,
                   &db::warehouse::available_capacity),
    std::make_pair(&WarehouseDTO::manager_rk_id, &db::warehouse::manager_rk_id),
    std::make_pair(&WarehouseDTO::phone, &db::warehouse::phone),  // 新增
    std::make_pair(&WarehouseDTO::created_at,
                   &db::warehouse::created_at),                     // 新增
    std::make_pair(&WarehouseDTO::status, &db::warehouse::status),  // 新增
    std::make_pair(&WarehouseDTO::remark, &db::warehouse::remark));
};

template <typename WarehouseRow>
struct ReflectTableRow<WarehouseDTO, WarehouseRow> {
  static WarehouseDTO assign_model(WarehouseRow&& row)
  {
    return WarehouseDTO{.id = row.id,
                        .warehouse_id = row.warehouse_id,
                        .warehouse_name = row.warehouse_name,
                        .location = row.location,
                        .capacity = row.capacity,
                        .available_capacity = row.available_capacity,
                        .manager_rk_id = row.manager_rk_id,
                        .phone = row.phone,            // 新增
                        .created_at = row.created_at,  // 新增
                        .status = row.status,          // 新增
                        .remark = row.remark};
  }
};
}  // namespace model
