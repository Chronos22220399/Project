#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/member/member_level_repository.h>
#include <service/member/member_level_service.h>

using json = nlohmann::json;

ServiceResult MemberLevelService::create(MemberLevelDTO& dto)
{
  return {false, "Not implemented yet."};
}

ServiceResult MemberLevelService::updateByLevelId(const std::string& level_id,
                                                  MemberLevelDTO& dto)
{
  return {false, "Not implemented yet."};
}

ServiceResult MemberLevelService::removeByLevelId(const std::string& level_id)
{
  return {false, "Not implemented yet."};
}

ServiceResult MemberLevelService::getByPage(const int page, const int page_size)
{
  return {false, "Not implemented yet."};
}

ServiceResult MemberLevelService::getAll()
{
  return {false, "Not implemented yet."};
}
