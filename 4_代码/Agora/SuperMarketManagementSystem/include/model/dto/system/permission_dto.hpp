#pragma once
#include <common/cache_func_getter.h>
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/system/permission.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for permission table
struct PermissionDTO : public CacheFuncGetter {
  inline static const std::vector<std::string> required_fields = {
    "permission_id",    //
    "permission_name",  //
    "permission_code",  //
    "description",      //

  };

  in_id_type id = 0;
  std::string permission_id = "";
  std::string permission_name = "";
  std::string permission_code = "";
  std::string description = "";
  datetime_type created_at = {};

  // JSON serialization/deserialization
  static PermissionDTO from_json(const nlohmann::json& j)
  {
    try {
      return PermissionDTO{
        .permission_id = j.at("permission_id").get<std::string>(),
        .permission_name = j.at("permission_name").get<std::string>(),
        .permission_code = j.at("permission_code").get<std::string>(),
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

inline void to_json(nlohmann::json& j, const PermissionDTO& permission_dto)
{
  j = nlohmann::json{
    {"id", permission_dto.id},
    {"permission_id", permission_dto.permission_id},
    {"permission_name", permission_dto.permission_name},
    {"permission_code", permission_dto.permission_code},
    {"description", permission_dto.description},
    {"created_at", utils::datetime_to_string(permission_dto.created_at)}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<PermissionDTO, db::permission> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&PermissionDTO::id, &db::permission::id),
    std::make_pair(&PermissionDTO::permission_id,
                   &db::permission::permission_id),
    std::make_pair(&PermissionDTO::permission_name,
                   &db::permission::permission_name),
    std::make_pair(&PermissionDTO::permission_code,
                   &db::permission::permission_code),
    std::make_pair(&PermissionDTO::description, &db::permission::description),
    std::make_pair(&PermissionDTO::created_at, &db::permission::created_at));
};

// mapping
template <typename PermissionRow>
struct ReflectTableRow<PermissionDTO, PermissionRow> {
  static PermissionDTO assign_model(PermissionRow&& row)
  {
    return PermissionDTO{.id = row.id,
                         .permission_id = row.permission_id,
                         .permission_name = row.permission_name,
                         .permission_code = row.permission_code,
                         .description = row.description,
                         .created_at = row.created_at};
  }
};
}  // namespace model
