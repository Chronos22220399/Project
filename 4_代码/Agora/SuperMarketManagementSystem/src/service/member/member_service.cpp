#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/member/member_repository.h>
#include <service/member/member_service.h>

using json = nlohmann::json;
using namespace std::chrono;

ServiceResult MemberService::create(MemberDTO& member_dto)
{
  auto& cache = GlobalIdCache::getInstance();
  // 检查 status 范围
  if (!utils::in(member_dto.status, MemberDTO::status_domain))
    return {false, "Status out of range."};
  // 检查用户是否存在
  if (member_dto.user_rk_id == 0)
    return {false, "No such user."};
  // 检查等级是否存在
  if (member_dto.level_rk_id == 0)
    return {false, "No such level."};

  // 检查用户是否是会员
  if (MemberRepository::findMemberByUserRKId(member_dto.user_rk_id))
    return {false, "User is member."};

  // 设置会员 id
  member_dto.member_id = utils::create_id("Mem-");
  // 设置注册日期
  member_dto.registration_date = system_clock::now();
  member_dto.points = 0.0;

  // 创建
  auto res = MemberRepository::create(member_dto);
  if (!res)
    return {false, "Create member failed, please check out endpoint log."};
  cache.update("member", member_dto.member_id, res.value());
  return {true};
}

ServiceResult MemberService::updateByMemberId(const std::string& member_id,
                                              MemberDTO& member_dto)
{
  auto& cache = GlobalIdCache::getInstance();

  // 检查 status 范围
  if (!utils::in(member_dto.status, MemberDTO::status_domain))
    return {false, "Status out of range."};
  // 检查用户是否存在
  if (member_dto.user_rk_id == 0)
    return {false, "No such user."};
  // 检查等级是否存在
  if (member_dto.level_rk_id == 0)
    return {false, "No such level."};

  // 判断会员是否存在
  if (member_dto.id == 0)
    return {false, "No such member."};
  // 判断用户是否是会员
  auto id = MemberRepository::findMemberByUserRKId(member_dto.user_rk_id);
  if (!id.has_value())
    return {false, "User is not member."};
  // 检测传入的用户的会员账号
  if (id.value() != member_dto.id)
    return {false, "Member info not matched."};

  auto success = MemberRepository::updateById(id.value(), member_dto);
  if (!success)
    return {false, "Create member failed."};
  return {true};
}

ServiceResult MemberService::removeByMemberId(const std::string& member_id)
{
  auto id = GlobalIdCache::getInstance().getInternalId("member", member_id);
  if (id == 0)
    return {false, "Member does not exists."};

  auto success = MemberRepository::removeById(id);
  if (!success)
    return {false, "Remove member is failed."};
  return {true};
}

ServiceResult MemberService::getByPage(const int page, const int page_size)
{
  // 校验分页参数有效性
  if (page < 1 || page_size < 1) {
    return {false, "Invalid page or page_size"};
  }

  auto offset = (page - 1) * page_size;

  // 获取商品价格总数
  count_type total = MemberRepository::count();
  auto goods_price_list = MemberRepository::getByPage(page_size, offset);

  nlohmann::json data{{"success", true},
                      {"total", total},
                      {"page", page},
                      {"page_size", page_size},
                      {"items", goods_price_list}};

  return {true, "", data};
}

ServiceResult MemberService::getAll()
{
  return {false, "Not implemented yet."};
}
