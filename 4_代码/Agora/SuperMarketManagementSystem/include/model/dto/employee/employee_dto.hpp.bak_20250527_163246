#pragma once
#include <common/cache_func_getter.h>
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/employee/employee.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for employee table
struct EmployeeDTO : public CacheFuncGetter {
  inline static const std::vector<std::string> required_fields = {
    "employee_id",    //
    "user_id",        //
    "employee_name",  //
    "gender",         //
    "birthday",       //
    "id_number",      //
    "hire_date",      //
    "position_id",    //
    "status",         //
    "address"         //
  };
  inline static const std::vector<std::string> status_domain = {
    "active",    //
    "inactive",  //
    "on_leave"   //
  };

  in_id_type id = 0;
  std::string employee_id = "";
  in_id_type user_rk_id = 0;
  std::string employee_name = "";
  std::string gender = "";
  date_type birthday = {};
  std::string id_number = "";
  datetime_type hire_date = {};
  in_id_type position_rk_id = 0;
  std::string status = "";
  std::string address = "";

  // JSON serialization/deserialization
  static EmployeeDTO from_json(const nlohmann::json& j)
  {
    try {
      return EmployeeDTO{
        .employee_id = j.at("employee_id").get<std::string>(),
        .user_rk_id = getInternalId("user", j.at("user_id").get<ex_id_type>()),
        .employee_name = j.at("employee_name").get<std::string>(),
        .gender = j.at("gender").get<std::string>(),
        .birthday = utils::string_to_date(j.at("birthday").get<std::string>()),
        .id_number = j.at("id_number").get<std::string>(),
        .hire_date =
          utils::string_to_datetime(j.at("hire_date").get<std::string>()),
        .position_rk_id =
          getInternalId("position", j.at("position_id").get<ex_id_type>()),
        .status = j.at("status").get<std::string>(),
        .address = j.at("address").get<std::string>(),
      };
    }
    catch (const std::exception& e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json& j, const EmployeeDTO& employee_dto)
{
  j = nlohmann::json{
    {"employee_id", employee_dto.employee_id},
    {"user_id",
     EmployeeDTO::getExternalId("employee", employee_dto.user_rk_id)},
    {"employee_name", employee_dto.employee_name},
    {"gender", employee_dto.gender},
    {"birthday", utils::date_to_string(employee_dto.birthday)},
    {"id_number", employee_dto.id_number},
    {"hire_date", utils::datetime_to_string(employee_dto.hire_date)},
    {"position_id",
     EmployeeDTO::getExternalId("position", employee_dto.position_rk_id)},
    {"status", employee_dto.status},
    {"address", employee_dto.address}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<EmployeeDTO, db::employee> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&EmployeeDTO::id, &db::employee::id),
    std::make_pair(&EmployeeDTO::employee_id, &db::employee::employee_id),
    std::make_pair(&EmployeeDTO::user_rk_id, &db::employee::user_rk_id),
    std::make_pair(&EmployeeDTO::employee_name, &db::employee::employee_name),
    std::make_pair(&EmployeeDTO::gender, &db::employee::gender),
    std::make_pair(&EmployeeDTO::birthday, &db::employee::birthday),
    std::make_pair(&EmployeeDTO::id_number, &db::employee::id_number),
    std::make_pair(&EmployeeDTO::hire_date, &db::employee::hire_date),
    std::make_pair(&EmployeeDTO::position_rk_id, &db::employee::position_rk_id),
    std::make_pair(&EmployeeDTO::status, &db::employee::status),
    std::make_pair(&EmployeeDTO::address, &db::employee::address));
};

// mapping
template <typename EmployeeRow>
struct ReflectTableRow<EmployeeDTO, EmployeeRow> {
  static EmployeeDTO assign_model(EmployeeRow&& row)
  {
    return EmployeeDTO{.id = row.id,
                       .employee_id = row.employee_id,
                       .user_rk_id = row.user_rk_id,
                       .employee_name = row.employee_name,
                       .gender = row.gender,
                       .birthday = row.birthday,
                       .id_number = row.id_number,
                       .hire_date = row.hire_date,
                       .position_rk_id = row.position_rk_id,
                       .status = row.status,
                       .address = row.address};
  }
};
}  // namespace model
