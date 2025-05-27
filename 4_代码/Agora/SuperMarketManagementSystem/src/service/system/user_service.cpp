#include <common/common_utils.hpp>
#include <common/user/jwt_manager.hpp>
#include <common/user/vcode_manager.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <regex>
#include <repository/system/user_repository.h>
#include <service/system/user_service.h>

using json = nlohmann::json;
using namespace std::chrono;


ServiceResult UserService::getVCode(const std::string& phone)
{
  // 简单正则校验手机号格式（可根据需要调整）
  std::regex phone_regex("^1[3-9]\\d{9}$");
  if (!std::regex_match(phone, phone_regex))
    return {false, "Invalid phone number format."};

  auto& vcodeMgr = VCodeManager::getInstance();
  std::string code = vcodeMgr.generateCode(phone);

  // TODO: 集成实际短信服务商，这里仅 mock 返回
  // 出于安全考虑，实际环境不要直接把验证码返回前端，这里仅便于调试
  nlohmann::json data = {{"phone", phone}, {"vcode", code}};
  return {true, "", data};
}


ServiceResult UserService::regist(const std::string& vcode, UserDTO& user_dto)
{
  // 检验验证码是否过期
  auto& vcodeMgr = VCodeManager::getInstance();
  auto verifyRes = vcodeMgr.verifyCode(user_dto.phone_number, vcode);
  if (!verifyRes.success)
    return {false, verifyRes.error};

  auto check_res = uniCheck(user_dto);
  if (!check_res.success)
    return check_res;

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


// MARK: 登陆
ServiceResult UserService::login(const std::string& username,
                                 const std::string& password)
{
  if (!password_is_valid(password))
    return {false, "Password invalid."};

  // 查找用户
  auto res = UserRepository::getUserByUsername(username);
  if (res.empty())
    return {false, "Username could not found."};

  auto hassed_passwd = res.front().password;
  auto _passwd = password;
  auto hassed_password = hash_password(_passwd);

  if (!hassed_password.has_value())
    return {false, "Hash password failed."};
  if (hassed_password.value() != hassed_passwd)
    return {false, "Password not matched."};

  auto& jwt = JwtManager::getInstance();
  auto user_id = res.front().user_id;
  auto token = jwt.generateToken(user_id);

  return {true, "", {"token", token}};
}


ServiceResult UserService::updateByUserId(const std::string& user_id,
                                          const bool change_password,
                                          UserDTO& user_dto)
{
  auto check_res = uniCheck(user_dto);
  if (!check_res.success)
    return check_res;

  if (change_password) {
    // 哈希密码
    auto hashed_password = hash_password(user_dto.password);
    if (!hashed_password.has_value())
      return {false, "System Error."};
    user_dto.password = hashed_password.value();
  }

  auto& cache = GlobalIdCache::getInstance();
  auto id = cache.getInternalId("user", user_id);
  // 更新用户信息
  auto res = UserRepository::updateById(id, user_dto);
  if (!res)
    return {false, "Update user failed."};
  return {true};
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

bool UserService::password_is_valid(const std::string& password)
{
  if (password.empty() || password.size() < 8)
    return false;
  return true;
}

// TODO: 添加哈希密码的逻辑
std::optional<std::string> UserService::hash_password(std::string& password)
{
  try {
    // auto hashed_password =
  }
  catch (const std::exception& e) {
    LOG("Hash password failed, reason is: {}", e.what());
  }
  return std::nullopt;
}


// 通用检查
ServiceResult UserService::uniCheck(UserDTO& user_dto)
{
  //  检测字段是否在范围内
  if (!utils::in(user_dto.status, UserDTO::status_domain))
    return {false, "Status out of domain."};
  // 检测密码是否合法
  if (!password_is_valid(user_dto.password))
    return {false, "Please check your password whether valid."};

  // 检测用户名是否存在
  if (UserRepository::findUserName(user_dto.username))
    return {false, "Username has been used."};
  // 检测手机号是否存在
  if (UserRepository::findPhone(user_dto.phone_number))
    return {false, "Your phone number have been used."};
  return {true};
}
