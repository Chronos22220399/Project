#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/member/member_repository.h>
#include <service/member/member_service.h>

using json = nlohmann::json;

ServiceResult MemberService::create(MemberDTO& dto)
{
  return {false, "Not implemented yet."};
}

ServiceResult MemberService::updateByMemberId(const std::string& ex_id,
                                              MemberDTO& dto)
{
  return {false, "Not implemented yet."};
}

ServiceResult MemberService::removeByMemberId(const std::string& ex_id)
{
  return {false, "Not implemented yet."};
}

ServiceResult MemberService::getByPage(const int page, const int page_size)
{
  return {false, "Not implemented yet."};
}

ServiceResult MemberService::getAll()
{
  return {false, "Not implemented yet."};
}
