#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/warehouse/warehouse.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for warehouse table

struct WarehouseDTO {
  in_id_type id = 0;
  ex_id_type warehouse_id = "";
  std::string warehouse_name = "";
  std::string location = "";
  slot_mount_type total_slots = 0;
  slot_mount_type available_slots;
  std::string manager;
  std::string description;

  // JSON serialization/deserialization
  static WarehouseDTO from_json(const nlohmann::json &j) {
    try {
      return WarehouseDTO{
          .warehouse_id = j.at("warehouse_id").get<ex_id_type>(),
          .warehouse_name = j.at("warehouse_name").get<std::string>(),
          .location = j.at("location").get<std::string>(),
          .total_slots = j.at("total_slots").get<slot_mount_type>(),
          .available_slots = j.at("available_slots").get<slot_mount_type>(),
          .manager = j.at("manager").get<std::string>(),
          .description = j.at("description").get<std::string>()};
    } catch (const std::exception &e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json &j, const WarehouseDTO &warehouse_dto) {
  j = nlohmann::json{{"warehouse_id", warehouse_dto.warehouse_id},
                     {"warehouse_name", warehouse_dto.warehouse_name},
                     {"location", warehouse_dto.location},
                     {"total_slots", warehouse_dto.total_slots},
                     {"available_slots", warehouse_dto.available_slots},
                     {"manager", warehouse_dto.manager},
                     {"description", warehouse_dto.description}};
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
      std::make_pair(&WarehouseDTO::total_slots,
                     &db::warehouse::total_slots), // 新增
      std::make_pair(&WarehouseDTO::available_slots,
                     &db::warehouse::available_slots),                 // 新增
      std::make_pair(&WarehouseDTO::manager, &db::warehouse::manager), // 新增
      std::make_pair(&WarehouseDTO::description,
                     &db::warehouse::description)); // 新增
};

template <typename WarehouseRow>
struct ReflectTableRow<WarehouseDTO, WarehouseRow> {
  static WarehouseDTO assign_model(WarehouseRow &&row) {
    return WarehouseDTO{.id = row.id,
                        .warehouse_id = row.warehouse_id,
                        .warehouse_name = row.warehouse_name,
                        .location = row.location,
                        .total_slots = row.total_slots,         // 新增
                        .available_slots = row.available_slots, // 新增
                        .manager = row.manager,                 // 新增
                        .description = row.description};        // 新增
  }
};
} // namespace model
