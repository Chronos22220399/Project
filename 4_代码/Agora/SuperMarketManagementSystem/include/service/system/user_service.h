#pragma once
#include <crow.h>
#include <model/dto/system/user_dto.hpp>
#include <string>


class UserService {
  public:
  static ServiceResult create(UserDTO& dto);
  static ServiceResult updateByUserId(const std::string& ex_id, UserDTO& dto);
  static ServiceResult removeByUserId(const std::string& ex_id);
  static ServiceResult getByPage(const int page, const int page_size);
  static ServiceResult getAll();

  // check password
  static bool password_is_valid(std::string& password);
  // hash password
  static std::optional<bool> hash_password(std::string& password);
};
