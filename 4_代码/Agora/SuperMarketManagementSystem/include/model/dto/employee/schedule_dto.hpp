#pragma once
#include <common/cache_func_getter.h>
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/employee/schedule.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for schedule table
struct ScheduleDTO : public CacheFuncGetter {
  inline static const std::vector<std::string> required_fields = {
    "schedule_id",    //
    "employee_id",    //
    "schedule_date",  //
    "start_time",     //
    "end_time",       //
    "created_by"      //
  };

  in_id_type id = 0;
  std::string schedule_id = "";
  in_id_type employee_rk_id = 0;
  datetime_type schedule_date = {};
  time_type start_time = {};
  time_type end_time = {};
  datetime_type created_at = {};
  in_id_type created_by = 0;

  // JSON serialization/deserialization
  static ScheduleDTO from_json(const nlohmann::json& j)
  {
    try {
      return ScheduleDTO{
        .schedule_id = j.at("schedule_id").get<std::string>(),
        .employee_rk_id =
          getInternalId("employee", j.at("employee_id").get<ex_id_type>()),
        .schedule_date =
          utils::string_to_datetime(j.at("schedule_date").get<std::string>()),
        .start_time = j.at("start_time").get<time_type>(),
        .end_time = j.at("end_time").get<time_type>(),
        .created_at =
          utils::string_to_datetime(j.at("created_at").get<std::string>()),
        .created_by =
          getInternalId("employee", j.at("created_by").get<ex_id_type>()),
      };
    }
    catch (const std::exception& e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json& j, const ScheduleDTO& schedule_dto)
{
  j = nlohmann::json{
    {"schedule_id", schedule_dto.schedule_id},
    {"employee_id",
     ScheduleDTO::getExternalId("employee", schedule_dto.employee_rk_id)},
    {"schedule_date", utils::datetime_to_string(schedule_dto.schedule_date)},
    {"start_time", schedule_dto.start_time},
    {"end_time", schedule_dto.end_time},
    {"created_at", utils::datetime_to_string(schedule_dto.created_at)},
    {"created_by",
     ScheduleDTO::getExternalId("employee", schedule_dto.created_by)}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<ScheduleDTO, db::schedule> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&ScheduleDTO::id, &db::schedule::id),
    std::make_pair(&ScheduleDTO::schedule_id, &db::schedule::schedule_id),
    std::make_pair(&ScheduleDTO::employee_rk_id, &db::schedule::employee_rk_id),
    std::make_pair(&ScheduleDTO::schedule_date, &db::schedule::schedule_date),
    std::make_pair(&ScheduleDTO::start_time, &db::schedule::start_time),
    std::make_pair(&ScheduleDTO::end_time, &db::schedule::end_time),
    std::make_pair(&ScheduleDTO::created_at, &db::schedule::created_at),
    std::make_pair(&ScheduleDTO::created_by, &db::schedule::created_by));
};

// mapping
template <typename ScheduleRow>
struct ReflectTableRow<ScheduleDTO, ScheduleRow> {
  static ScheduleDTO assign_model(ScheduleRow&& row)
  {
    return ScheduleDTO{.id = row.id,
                       .schedule_id = row.schedule_id,
                       .employee_rk_id = row.employee_rk_id,
                       .schedule_date = row.schedule_date,
                       .start_time = row.start_time,
                       .end_time = row.end_time,
                       .created_at = row.created_at,
                       .created_by = row.created_by};
  }
};
}  // namespace model
