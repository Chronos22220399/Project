#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/system/role_repository.h>
#include <service/system/role_service.h>

using json = nlohmann::json;

ServiceResult RoleService::create(RoleDTO& dto)
{
  return {false, "Not implemented yet."};
}

ServiceResult RoleService::updateByRoleId(const std::string& ex_id,
                                          RoleDTO& dto)
{
  return {false, "Not implemented yet."};
}

ServiceResult RoleService::removeByRoleId(const std::string& ex_id)
{
  return {false, "Not implemented yet."};
}

ServiceResult RoleService::getByPage(const int page, const int page_size)
{
  return {false, "Not implemented yet."};
}

ServiceResult RoleService::getAll()
{
  return {false, "Not implemented yet."};
}
