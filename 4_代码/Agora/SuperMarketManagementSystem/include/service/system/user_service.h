#pragma once
#include <crow.h>
#include <model/dto/system/user_dto.hpp>
#include <string>


class UserService {
  public:
  static ServiceResult regist(const std::string& vcode, UserDTO& dto);
  static ServiceResult updateByUserId(const std::string& user_id,
                                      const bool hash, UserDTO& dto);
  static ServiceResult removeByUserId(const std::string& user_id);
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getAll();

  // 通用检查
  static ServiceResult uniCheck(UserDTO& user_dto);

  // 登陆
  static ServiceResult login(const std::string& username,
                             const std::string& password);

  // check password
  static bool password_is_valid(const std::string& password);
  // hash password
  static std::optional<std::string> hash_password(std::string& password);
};
