#pragma once
#include <common/cache_func_getter.h>
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/system/system_update_log.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for system_update_log table
struct SystemUpdateLogDTO : public CacheFuncGetter {
  inline static const std::vector<std::string> required_fields = {
    "external_id",      //
    "version",          //
    "update_id",        //
    "update_type",      //
    "description",      //
    "change_summary",   //
    "affected_modules"  //
  };
  inline static const std::vector<std::string> update_type_domain = {
    "patch",    //
    "upgrade",  //
  };

  in_id_type id = 0;
  std::string update_id = "";
  std::string version = "";
  in_id_type user_rk_id = 0;
  std::string update_type = "";
  datetime_type updated_at = {};
  std::string description = "";
  std::string change_summary = "";
  std::string affected_modules = "";

  // JSON serialization/deserialization
  static SystemUpdateLogDTO from_json(const nlohmann::json& j)
  {
    try {
      return SystemUpdateLogDTO{
        .update_id = j.at("update_id").get<std::string>(),
        .version = j.at("version").get<std::string>(),
        .user_rk_id = getInternalId("user", j.at("user_id").get<ex_id_type>()),
        .update_type = j.at("update_type").get<std::string>(),
        .description = j.at("description").get<std::string>(),
        .change_summary = j.at("change_summary").get<std::string>(),
        .affected_modules = j.at("affected_modules").get<std::string>(),
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
                    const SystemUpdateLogDTO& system_update_log_dto)
{
  j = nlohmann::json{
    {"update_id", system_update_log_dto.update_id},
    {"version", system_update_log_dto.version},
    {"user_id", SystemUpdateLogDTO::getExternalId(
                  "user", system_update_log_dto.user_rk_id)},
    {"update_type", system_update_log_dto.update_type},
    {"updated_at", utils::datetime_to_string(system_update_log_dto.updated_at)},
    {"description", system_update_log_dto.description},
    {"change_summary", system_update_log_dto.change_summary},
    {"affected_modules", system_update_log_dto.affected_modules}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<SystemUpdateLogDTO, db::system_update_log> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&SystemUpdateLogDTO::id, &db::system_update_log::id),
    std::make_pair(&SystemUpdateLogDTO::update_id,
                   &db::system_update_log::update_id),
    std::make_pair(&SystemUpdateLogDTO::version,
                   &db::system_update_log::version),
    std::make_pair(&SystemUpdateLogDTO::user_rk_id,
                   &db::system_update_log::user_rk_id),
    std::make_pair(&SystemUpdateLogDTO::update_type,
                   &db::system_update_log::update_type),
    std::make_pair(&SystemUpdateLogDTO::updated_at,
                   &db::system_update_log::updated_at),
    std::make_pair(&SystemUpdateLogDTO::description,
                   &db::system_update_log::description),
    std::make_pair(&SystemUpdateLogDTO::change_summary,
                   &db::system_update_log::change_summary),
    std::make_pair(&SystemUpdateLogDTO::affected_modules,
                   &db::system_update_log::affected_modules));
};

// mapping
template <typename System_update_logRow>
struct ReflectTableRow<SystemUpdateLogDTO, System_update_logRow> {
  static SystemUpdateLogDTO assign_model(System_update_logRow&& row)
  {
    return SystemUpdateLogDTO{.id = row.id,
                              .update_id = row.updated_id,
                              .version = row.version,
                              .user_rk_id = row.user_rk_id,
                              .update_type = row.update_type,
                              .updated_at = row.updated_at,
                              .description = row.description,
                              .change_summary = row.change_summary,
                              .affected_modules = row.affected_modules};
  }
};
}  // namespace model
