#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/warehouse/warehouse.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for warehouse table
struct WarehouseDTO {
  id_type id = 0;
  std::string warehouse_id = "";
  std::string warehouse_name = "";
  std::string location = "";

  // JSON serialization/deserialization
  static WarehouseDTO from_json(const nlohmann::json &j) {
    try {
      return WarehouseDTO{
          .warehouse_id = j.at("warehouse_id").get<std::string>(),
          .warehouse_name = j.at("warehouse_name").get<std::string>(),
          .location = j.at("location").get<std::string>(),
      };
    } catch (const std::exception &e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json &j, const WarehouseDTO &warehouse_dto) {
  j = nlohmann::json{{"id", warehouse_dto.id},
                     {"warehouse_id", warehouse_dto.warehouse_id},
                     {"warehouse_name", warehouse_dto.warehouse_name},
                     {"location", warehouse_dto.location}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<WarehouseDTO, db::warehouse> {
  static constexpr auto map_members = std::make_tuple(
      std::make_pair(&WarehouseDTO::id, &db::warehouse::id),
      std::make_pair(&WarehouseDTO::warehouse_id, &db::warehouse::warehouse_id),
      std::make_pair(&WarehouseDTO::warehouse_name,
                     &db::warehouse::warehouse_name),
      std::make_pair(&WarehouseDTO::location, &db::warehouse::location));
};

// mapping
template <typename WarehouseRow>
struct ReflectTableRow<WarehouseDTO, WarehouseRow> {
  static WarehouseDTO assign_model(WarehouseRow &&row) {
    return WarehouseDTO{.id = row.id,
                        .warehouse_id = row.warehouse_id,
                        .warehouse_name = row.warehouse_name,
                        .location = row.location};
  }
};
} // namespace model
