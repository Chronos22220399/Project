#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/common/unit.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for unit table
struct UnitDTO {
  inline static const std::vector<std::string> required_fields = {
    "unit_id",
    "unit_name"  // 单位名称
  };

  in_id_type id = 0;
  std::string unit_id = "";
  std::string unit_name = "";

  // JSON serialization/deserialization
  static UnitDTO from_json(const nlohmann::json &j) {
    try {
      return UnitDTO{
          .unit_id = j.at("unit_id").get<std::string>(),
          .unit_name = j.at("unit_name").get<std::string>(),
      };
    } catch (const std::exception &e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json &j, const UnitDTO &unit_dto) {
  j = nlohmann::json{{"unit_id", unit_dto.unit_id},
                     {"unit_name", unit_dto.unit_name}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<UnitDTO, db::unit> {
  static constexpr auto map_members = std::make_tuple(
      std::make_pair(&UnitDTO::id, &db::unit::id),
      std::make_pair(&UnitDTO::unit_id, &db::unit::unit_id),
      std::make_pair(&UnitDTO::unit_name, &db::unit::unit_name));
};

// mapping
template <typename UnitRow> struct ReflectTableRow<UnitDTO, UnitRow> {
  static UnitDTO assign_model(UnitRow &&row) {
    return UnitDTO{
        .id = row.id, .unit_id = row.unit_id, .unit_name = row.unit_name};
  }
};
} // namespace model
