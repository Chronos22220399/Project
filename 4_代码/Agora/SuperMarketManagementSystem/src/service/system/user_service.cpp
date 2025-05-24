#include <common/common_utils.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <repository/system/user_repository.h>
#include <service/system/user_service.h>

using json = nlohmann::json;
using namespace std::chrono;

ServiceResult UserService::create(UserDTO& user_dto)
{
  //  检测字段是否在范围内
  if (!utils::in(user_dto.status, UserDTO::status_domain))
    return {false, "Status out of domain."};

  // 检测用户名是否存在
  if (UserRepository::findUserName(user_dto.username))
    return {false, "Username has been used."};
  // 检测手机号是否存在
  if (UserRepository::findPhone(user_dto.phone_number))
    return {false, "Your phone number have been used."};
  // 检测密码是否合法
  if (!password_is_valid(user_dto.password))
    return {false, "Please check your password whether valid."};
  // 哈希密码
  auto hashed_password = hash_password(user_dto.password);
  if (!hashed_password.has_value())
    return {false, "System Error."};
  user_dto.password = hashed_password.value();
  // 创建用户外部 id
  user_dto.user_id = utils::create_id("USER-");
  // 创建创建时间
  user_dto.created_at = time_point_cast<microseconds>(system_clock::now());
  // 创建用户
  auto res = UserRepository::create(user_dto);
  if (!res.has_value())
    return {false, "Create user failed."};
  // 更新缓存
  UserDTO::update("user", user_dto.user_id, user_dto.id);
  return {true};
}

ServiceResult UserService::updateByUserId(const std::string& ex_id,
                                          UserDTO& dto)
{
  return {false, "Not implemented yet."};
}

ServiceResult UserService::removeByUserId(const std::string& ex_id)
{
  return {false, "Not implemented yet."};
}

ServiceResult UserService::getByPage(const int page, const int page_size)
{
  return {false, "Not implemented yet."};
}

ServiceResult UserService::getAll()
{
  return {false, "Not implemented yet."};
}

bool UserService::password_is_valid(std::string& password)
{
  if (password.empty() || password.size() < 8)
    return false;
  return true;
}

// TODO: 添加哈希密码的逻辑
std::optional<bool> UserService::hash_password(std::string& password)
{
  try {
    // auto hashed_password =
  }
  catch (const std::exception& e) {
    LOG("Hash password failed, reason is: {}", e.what());
  }
  return std::nullopt;
}
