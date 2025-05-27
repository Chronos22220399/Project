#pragma once
#include <common/cache_func_getter.h>
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/system/system_setting.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for system_setting table
struct SystemSettingDTO : public CacheFuncGetter {
  inline static const std::vector<std::string> required_fields = {
    "setting_key",    //
    "setting_value",  //
    "description",    //
    "updater_id",     //
  };

  std::string setting_key = 0;
  std::string setting_value = "";
  std::string description = "";
  datetime_type updated_at = {};
  in_id_type updater_rk_id = 0;

  // JSON serialization/deserialization
  static SystemSettingDTO from_json(const nlohmann::json& j)
  {
    try {
      return SystemSettingDTO{
        .setting_value = j.at("setting_value").get<std::string>(),
        .description = j.at("description").get<std::string>(),
        .updated_at =
          utils::string_to_datetime(j.at("updated_at").get<std::string>()),
        .updater_rk_id =
          getInternalId("user", j.at("updater_id").get<ex_id_type>()),
      };
    }
    catch (const std::exception& e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json& j,
                    const SystemSettingDTO& system_setting_dto)
{
  j = nlohmann::json{
    {"setting_key", system_setting_dto.setting_key},
    {"setting_value", system_setting_dto.setting_value},
    {"description", system_setting_dto.description},
    {"updated_at", utils::datetime_to_string(system_setting_dto.updated_at)},
    {"updater_id", SystemSettingDTO::getExternalId(
                     "user", system_setting_dto.updater_rk_id)}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<SystemSettingDTO, db::system_setting> {
  static constexpr auto map_members =
    std::make_tuple(std::make_pair(&SystemSettingDTO::setting_key,
                                   &db::system_setting::setting_key),
                    std::make_pair(&SystemSettingDTO::setting_value,
                                   &db::system_setting::setting_value),
                    std::make_pair(&SystemSettingDTO::description,
                                   &db::system_setting::description),
                    std::make_pair(&SystemSettingDTO::updated_at,
                                   &db::system_setting::updated_at),
                    std::make_pair(&SystemSettingDTO::updater_rk_id,
                                   &db::system_setting::updater_rk_id));
};

// mapping
template <typename System_settingRow>
struct ReflectTableRow<SystemSettingDTO, System_settingRow> {
  static SystemSettingDTO assign_model(System_settingRow&& row)
  {
    return SystemSettingDTO{.setting_key = row.setting_key,
                            .setting_value = row.setting_value,
                            .description = row.description,
                            .updated_at = row.updated_at,
                            .updater_rk_id = row.updater_rk_id};
  }
};
}  // namespace model
