#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/employee/employee_repository.h>
#include <service/employee/employee_service.h>

using json = nlohmann::json;

ServiceResult EmployeeService::create(EmployeeDTO& dto)
{
  return {false, "Not implemented yet."};
}

ServiceResult EmployeeService::updateByEmployeeId(const std::string& ex_id,
                                                  EmployeeDTO& dto)
{
  return {false, "Not implemented yet."};
}

ServiceResult EmployeeService::removeByEmployeeId(const std::string& ex_id)
{
  return {false, "Not implemented yet."};
}

ServiceResult EmployeeService::getByPage(const int page, const int page_size)
{
  return {false, "Not implemented yet."};
}

ServiceResult EmployeeService::getAll()
{
  return {false, "Not implemented yet."};
}
