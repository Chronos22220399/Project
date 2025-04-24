#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/common/unit.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for unit table
struct UnitDTO {
    id_type id = 0;
std::string unit_id = "";
std::string unit_name = "";

    // JSON serialization/deserialization
    static UnitDTO from_json(const nlohmann::json& j) {
        try {
            return UnitDTO{
                .unit_id = j.at("unit_id"),
.unit_name = j.at("unit_name"),
            };
        } catch (const std::exception& e) {
            std::cerr << "[from_json error] " << e.what() << "\n"
                      << "Input JSON: " << j.dump(2) << std::endl;
            throw;
        }
    }
    
    nlohmann::json to_json() const {
        return {
            {"id", id},
{"unit_id", unit_id},
{"unit_name", unit_name}
        };
    }
};

// ORM mapping
namespace model {
template <>
struct ReflectTable<UnitDTO, db::unit> {
    static constexpr auto map_members = std::make_tuple(
        std::make_pair(&UnitDTO::id, &db::unit::id),
std::make_pair(&UnitDTO::unit_id, &db::unit::unit_id),
std::make_pair(&UnitDTO::unit_name, &db::unit::unit_name)
    );
};

// mapping
template <typename UnitRow> struct ReflectTableRow<UnitDTO, UnitRow> {
    static UnitDTO assign_model(UnitRow &&row) {
        return UnitDTO {
            .id = row.id,
.unit_id = row.unit_id,
.unit_name = row.unit_name
        };           
    }
};
} // namespace model
