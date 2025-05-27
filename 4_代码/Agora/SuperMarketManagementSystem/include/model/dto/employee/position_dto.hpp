#pragma once
#include <common/cache_func_getter.h>
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/employee/position.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for position table
struct PositionDTO : public CacheFuncGetter {
  inline static const std::vector<std::string> required_fields = {
    "position_id",//
    "position_name",//
    "base_salary",//
    "is_manager",//
    "department_name",//
    "description"//
    };

  in_id_type id = 0;
  std::string position_id = "";
  std::string position_name = "";
  double base_salary = 0.0;
  bool is_manager = false;
  std::string department_name = "";
  std::string description = "";

  // JSON serialization/deserialization
  static PositionDTO from_json(const nlohmann::json& j)
  {
    try {
      return PositionDTO{
        .position_id = j.at("position_id").get<std::string>(),
        .position_name = j.at("position_name").get<std::string>(),
        .base_salary = j.at("base_salary").get<double>(),
        .is_manager = j.at("is_manager").get<bool>(),
        .department_name = j.at("department_name").get<std::string>(),
        .description = j.at("description").get<std::string>(),
      };
    }
    catch (const std::exception& e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json& j, const PositionDTO& position_dto)
{
  j = nlohmann::json{{"id", position_dto.id},
                     {"position_id", position_dto.position_id},
                     {"position_name", position_dto.position_name},
                     {"base_salary", position_dto.base_salary},
                     {"is_manager", position_dto.is_manager},
                     {"department_name", position_dto.department_name},
                     {"description", position_dto.description}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<PositionDTO, db::position> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&PositionDTO::id, &db::position::id),
    std::make_pair(&PositionDTO::position_id, &db::position::position_id),
    std::make_pair(&PositionDTO::position_name, &db::position::position_name),
    std::make_pair(&PositionDTO::base_salary, &db::position::base_salary),
    std::make_pair(&PositionDTO::is_manager, &db::position::is_manager),
    std::make_pair(&PositionDTO::department_name,
                   &db::position::department_name),
    std::make_pair(&PositionDTO::description, &db::position::description));
};

// mapping
template <typename PositionRow>
struct ReflectTableRow<PositionDTO, PositionRow> {
  static PositionDTO assign_model(PositionRow&& row)
  {
    return PositionDTO{.id = row.id,
                       .position_id = row.position_id,
                       .position_name = row.position_name,
                       .base_salary = row.base_salary,
                       .is_manager = row.is_manager,
                       .department_name = row.department_name,
                       .description = row.description};
  }
};
}  // namespace model
