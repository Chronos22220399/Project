#pragma once
#include <common/cache_func_getter.h>
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/employee/attendance_record.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for attendance_record table
struct AttendanceRecordDTO : public CacheFuncGetter {
  inline static const std::vector<std::string> required_fields = {
    "record_id ", "employee_id", "date",       "clock_in",
    "clock_out",  "status",      "leave_type", "remark"};

  inline static const std::vector<std::string> status_domain = {
    "present", "late", "early_leave", "absent"};

  inline static const std::vector<std::string> leave_type_domain = {
    "sick_leave", "personal_leave", "annual_leave", "other"};

  in_id_type id = 0;
  std::string record_id = "";
  in_id_type employee_rk_id = 0;
  datetime_type date = {};
  datetime_type clock_in = {};
  datetime_type clock_out = {};
  std::string status = "";
  std::string leave_type = "";
  std::string remark = "";

  // JSON serialization/deserialization
  static AttendanceRecordDTO from_json(const nlohmann::json& j)
  {
    try {
      return AttendanceRecordDTO{
        .record_id = j.at("record_id").get<std::string>(),
        .employee_rk_id =
          getInternalId("employee", j.at("employee_rk_id").get<ex_id_type>()),
        .date = utils::string_to_date(j.at("date").get<std::string>()),
        .clock_in =
          utils::string_to_datetime(j.at("clock_in").get<std::string>()),
        .clock_out =
          utils::string_to_datetime(j.at("clock_out").get<std::string>()),
        .status = j.at("status").get<std::string>(),
        .leave_type = j.at("leave_type").get<std::string>(),
        .remark = j.at("remark").get<std::string>(),
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
                    const AttendanceRecordDTO& attendance_record_dto)
{
  j = nlohmann::json{
    {"id", attendance_record_dto.id},
    {"record_id", attendance_record_dto.record_id},
    {"employee_id", AttendanceRecordDTO::getExternalId(
                      "employee", attendance_record_dto.employee_rk_id)},
    {"date", utils::date_to_string(attendance_record_dto.date)},
    {"clock_in", utils::datetime_to_string(attendance_record_dto.clock_in)},
    {"clock_out", utils::datetime_to_string(attendance_record_dto.clock_out)},
    {"status", attendance_record_dto.status},
    {"leave_type", attendance_record_dto.leave_type},
    {"remark", attendance_record_dto.remark}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<AttendanceRecordDTO, db::attendance_record> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&AttendanceRecordDTO::id, &db::attendance_record::id),
    std::make_pair(&AttendanceRecordDTO::record_id,
                   &db::attendance_record::record_id),
    std::make_pair(&AttendanceRecordDTO::employee_rk_id,
                   &db::attendance_record::employee_rk_id),
    std::make_pair(&AttendanceRecordDTO::date, &db::attendance_record::date),
    std::make_pair(&AttendanceRecordDTO::clock_in,
                   &db::attendance_record::clock_in),
    std::make_pair(&AttendanceRecordDTO::clock_out,
                   &db::attendance_record::clock_out),
    std::make_pair(&AttendanceRecordDTO::status,
                   &db::attendance_record::status),
    std::make_pair(&AttendanceRecordDTO::leave_type,
                   &db::attendance_record::leave_type),
    std::make_pair(&AttendanceRecordDTO::remark,
                   &db::attendance_record::remark));
};

// mapping
template <typename Attendance_recordRow>
struct ReflectTableRow<AttendanceRecordDTO, Attendance_recordRow> {
  static AttendanceRecordDTO assign_model(Attendance_recordRow&& row)
  {
    return AttendanceRecordDTO{.id = row.id,
                               .record_id = row.record_id,
                               .employee_rk_id = row.employee_rk_id,
                               .date = row.date,
                               .clock_in = row.clock_in,
                               .clock_out = row.clock_out,
                               .status = row.status,
                               .leave_type = row.leave_type,
                               .remark = row.remark};
  }
};
}  // namespace model
