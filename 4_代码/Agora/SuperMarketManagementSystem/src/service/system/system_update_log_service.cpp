#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/system/system_update_log_repository.h>
#include <service/system/system_update_log_service.h>

using json = nlohmann::json;

ServiceResult SystemUpdateLogService::create(SystemUpdateLogDTO& dto)
{
  return {false, "Not implemented yet."};
}

ServiceResult SystemUpdateLogService::updateBySystemUpdateId(
  const std::string& update_id, SystemUpdateLogDTO& update_log_dto)
{
  return {false, "Not implemented yet."};
}

ServiceResult
SystemUpdateLogService::removeBySysremUpdateId(const std::string& update_id)
{
  return {false, "Not implemented yet."};
}

ServiceResult SystemUpdateLogService::getByPage(const int page,
                                                const int page_size)
{
  return {false, "Not implemented yet."};
}

ServiceResult SystemUpdateLogService::getAll()
{
  return {false, "Not implemented yet."};
}
