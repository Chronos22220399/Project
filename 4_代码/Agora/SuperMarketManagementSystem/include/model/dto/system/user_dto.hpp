#pragma once
#include <common/cache_func_getter.h>
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/system/user.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for user table
struct UserDTO : public CacheFuncGetter {
  inline static const std::vector<std::string> required_fields = {
    "user_id",       //
    "username",      //
    "password",      //
    "phone_number",  //
    "role_id",       //
    "status"         //
  };
  inline static const std::vector<std::string> status_domain = {
    "status",    // 状态字段取值说明：
    "active",    // 启用
    "inactive",  // 停用
    "locked",    // 锁定
  };

  in_id_type id;
  ex_id_type user_id = "";
  std::string username = "";
  std::string password = "";
  std::string phone_number = "";
  in_id_type role_rk_id = 0;
  std::string status = "";
  datetime_type created_at = {};
  datetime_type last_login_at = {};

  // JSON serialization/deserialization
  static UserDTO from_json(const nlohmann::json& j)
  {
    try {
      return UserDTO{
        .user_id = j.at("user_id").get<ex_id_type>(),
        .username = j.at("username").get<std::string>(),
        .password = j.at("password").get<std::string>(),
        .phone_number = j.at("phone").get<std::string>(),
        .role_rk_id = getInternalId("role", j.at("role_id").get<ex_id_type>()),
        .status = j.at("status").get<std::string>(),
      };
    }
    catch (const std::exception& e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json& j, const UserDTO& user_dto)
{
  j = nlohmann::json{
    {"user_id", user_dto.user_id},
    {"username", user_dto.username},
    {"password", user_dto.password},
    {"phone_number", user_dto.phone_number},
    {"role_id", UserDTO::getExternalId("user", user_dto.role_rk_id)},
    {"status", user_dto.status},
    {"created_at", utils::time_to_string(user_dto.created_at)},
    {"last_login_at", utils::time_to_string(user_dto.last_login_at)}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<UserDTO, db::user> {
  static constexpr auto map_members = std::make_tuple(
    std::make_tuple(&UserDTO::id, &db::user::id),
    std::make_pair(&UserDTO::user_id, &db::user::user_id),
    std::make_pair(&UserDTO::username, &db::user::username),
    std::make_pair(&UserDTO::password, &db::user::password_hash),
    std::make_pair(&UserDTO::phone_number, &db::user::phone_number),
    std::make_pair(&UserDTO::role_rk_id, &db::user::role_rk_id),
    std::make_pair(&UserDTO::status, &db::user::status),
    std::make_pair(&UserDTO::created_at, &db::user::created_at),
    std::make_pair(&UserDTO::last_login_at, &db::user::last_login_at));
};

// mapping
template <typename UserRow> struct ReflectTableRow<UserDTO, UserRow> {
  static UserDTO assign_model(UserRow&& row)
  {
    return UserDTO{.id = row.id,
                   .user_id = row.user_id,
                   .username = row.username,
                   .password = row.password_hash,
                   .phone_number = row.phone_number,
                   .role_rk_id = row.role_rk_id,
                   .status = row.status,
                   .created_at = row.created_at,
                   .last_login_at = row.last_login_at};
  }
};
}  // namespace model
