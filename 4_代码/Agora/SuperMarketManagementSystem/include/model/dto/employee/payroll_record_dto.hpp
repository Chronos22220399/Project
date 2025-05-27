#pragma once
#include <common/cache_func_getter.h>
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/employee/payroll_record.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for payroll_record table
struct PayrollRecordDTO : public CacheFuncGetter {
  inline static const std::vector<std::string> required_fields = {
    "payroll_record_id",  //
    "employee_id",        //
    "pay_period",         //
    "basic_salary",       //
    "bonus",              //
    "deduction",          //
    "net_salary",         //
    "paid_at"             //
  };


  in_id_type id = 0;
  std::string payroll_record_id = "";
  in_id_type employee_rk_id = 0;
  std::string pay_period = "";
  double basic_salary = 0.0;
  double bonus = 0.0;
  double deduction = 0.0;
  double net_salary = 0.0;
  datetime_type paid_at = {};

  // JSON serialization/deserialization
  static PayrollRecordDTO from_json(const nlohmann::json& j)
  {
    try {
      return PayrollRecordDTO{
        .payroll_record_id = j.at("payroll_record_id").get<std::string>(),
        .employee_rk_id =
          getInternalId("employee", j.at("employee_id").get<ex_id_type>()),
        .pay_period = j.at("pay_period").get<std::string>(),
        .basic_salary = j.at("basic_salary").get<double>(),
        .bonus = j.at("bonus").get<double>(),
        .deduction = j.at("deduction").get<double>(),
        .net_salary = j.at("net_salary").get<double>(),
        .paid_at =
          utils::string_to_datetime(j.at("paid_at").get<std::string>()),
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
                    const PayrollRecordDTO& payroll_record_dto)
{
  j = nlohmann::json{
    {"id", payroll_record_dto.id},
    {"payroll_record_id", payroll_record_dto.payroll_record_id},
    {"employee_id", PayrollRecordDTO::getExternalId(
                      "employee", payroll_record_dto.employee_rk_id)},
    {"pay_period", payroll_record_dto.pay_period},
    {"basic_salary", payroll_record_dto.basic_salary},
    {"bonus", payroll_record_dto.bonus},
    {"deduction", payroll_record_dto.deduction},
    {"net_salary", payroll_record_dto.net_salary},
    {"paid_at", utils::datetime_to_string(payroll_record_dto.paid_at)}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<PayrollRecordDTO, db::payroll_record> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&PayrollRecordDTO::id, &db::payroll_record::id),
    std::make_pair(&PayrollRecordDTO::payroll_record_id,
                   &db::payroll_record::payroll_record_id),
    std::make_pair(&PayrollRecordDTO::employee_rk_id,
                   &db::payroll_record::employee_rk_id),
    std::make_pair(&PayrollRecordDTO::pay_period,
                   &db::payroll_record::pay_period),
    std::make_pair(&PayrollRecordDTO::basic_salary,
                   &db::payroll_record::basic_salary),
    std::make_pair(&PayrollRecordDTO::bonus, &db::payroll_record::bonus),
    std::make_pair(&PayrollRecordDTO::deduction,
                   &db::payroll_record::deduction),
    std::make_pair(&PayrollRecordDTO::net_salary,
                   &db::payroll_record::net_salary),
    std::make_pair(&PayrollRecordDTO::paid_at, &db::payroll_record::paid_at));
};

// mapping
template <typename Payroll_recordRow>
struct ReflectTableRow<PayrollRecordDTO, Payroll_recordRow> {
  static PayrollRecordDTO assign_model(Payroll_recordRow&& row)
  {
    return PayrollRecordDTO{.id = row.id,
                            .payroll_record_id = row.payroll_record_id,
                            .employee_rk_id = row.employee_rk_id,
                            .pay_period = row.pay_period,
                            .basic_salary = row.basic_salary,
                            .bonus = row.bonus,
                            .deduction = row.deduction,
                            .net_salary = row.net_salary,
                            .paid_at = row.paid_at};
  }
};
}  // namespace model
