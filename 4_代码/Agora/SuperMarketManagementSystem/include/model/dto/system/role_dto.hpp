#pragma once
#include <common/cache_func_getter.h>
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/system/role.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for role table
struct RoleDTO : public CacheFuncGetter {
  inline static const std::vector<std::string> required_fields = {
    "role_id",      //
    "role_name",    //
    "description",  //
    "created_at"    //
  };

  in_id_type id = 0;
  std::string role_id = "";
  std::string role_name = "";
  std::string description = "";
  datetime_type created_at = {};

  // JSON serialization/deserialization
  static RoleDTO from_json(const nlohmann::json& j)
  {
    try {
      return RoleDTO{
        .role_id = j.at("role_id").get<std::string>(),
        .role_name = j.at("role_name").get<std::string>(),
        .description = j.at("description").get<std::string>(),
        .created_at =
          utils::string_to_datetime(j.at("created_at").get<std::string>()),
      };
    }
    catch (const std::exception& e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json& j, const RoleDTO& role_dto)
{
  j = nlohmann::json{
    {"id", role_dto.id},
    {"role_id", role_dto.role_id},
    {"role_name", role_dto.role_name},
    {"description", role_dto.description},
    {"created_at", utils::datetime_to_string(role_dto.created_at)}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<RoleDTO, db::role> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&RoleDTO::id, &db::role::id),
    std::make_pair(&RoleDTO::role_id, &db::role::role_id),
    std::make_pair(&RoleDTO::role_name, &db::role::role_name),
    std::make_pair(&RoleDTO::description, &db::role::description),
    std::make_pair(&RoleDTO::created_at, &db::role::created_at));
};

// mapping
template <typename RoleRow> struct ReflectTableRow<RoleDTO, RoleRow> {
  static RoleDTO assign_model(RoleRow&& row)
  {
    return RoleDTO{.id = row.id,
                   .role_id = row.role_id,
                   .role_name = row.role_name,
                   .description = row.description,
                   .created_at = row.created_at};
  }
};
}  // namespace model
