#pragma once
#include <common/cache_func_getter.h>
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/member/member.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for member table
struct MemberDTO : public CacheFuncGetter {
  inline static const std::vector<std::string> required_fields = {
    "member_id",          //
    "user_id",            //
    "registration_date",  //
    "level_id",           //
    "points",             //
    "gender",             //
    "birthday",           //
    "status"              //
  };
  inline static const std::vector<std::string> _domain = {
    "active",   // 活跃
    "inactive"  // 不活跃
  };

  in_id_type id = 0;
  std::string member_id = "";
  in_id_type user_rk_id = 0;
  datetime_type registration_date = {};
  in_id_type level_rk_id = 0;
  double points = 0.0;
  std::string gender = "";
  date_type birthday = {};
  std::string status = "";

  // JSON serialization/deserialization
  static MemberDTO from_json(const nlohmann::json& j)
  {
    try {
      return MemberDTO{
        .member_id = j.at("member_id").get<std::string>(),
        .user_rk_id = getInternalId("user", j.at("user_id").get<ex_id_type>()),
        .registration_date = utils::string_to_datetime(
          j.at("registration_date").get<std::string>()),
        .level_rk_id =
          getInternalId("level", j.at("level_id").get<ex_id_type>()),
        .points = j.at("points").get<double>(),
        .gender = j.at("gender").get<std::string>(),
        .birthday = utils::string_to_date(j.at("birthday").get<std::string>()),
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

inline void to_json(nlohmann::json& j, const MemberDTO& member_dto)
{
  j = nlohmann::json{
    {"member_id", member_dto.member_id},
    {"user_id", MemberDTO::getExternalId("user", member_dto.user_rk_id)},
    {"registration_date",
     utils::datetime_to_string(member_dto.registration_date)},
    {"level_id", MemberDTO::getExternalId("level", member_dto.level_rk_id)},
    {"points", member_dto.points},
    {"gender", member_dto.gender},
    {"birthday", utils::date_to_string(member_dto.birthday)},
    {"status", member_dto.status}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<MemberDTO, db::member> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&MemberDTO::id, &db::member::id),
    std::make_pair(&MemberDTO::member_id, &db::member::member_id),
    std::make_pair(&MemberDTO::user_rk_id, &db::member::user_rk_id),
    std::make_pair(&MemberDTO::registration_date,
                   &db::member::registration_date),
    std::make_pair(&MemberDTO::level_rk_id, &db::member::level_rk_id),
    std::make_pair(&MemberDTO::points, &db::member::points),
    std::make_pair(&MemberDTO::gender, &db::member::gender),
    std::make_pair(&MemberDTO::birthday, &db::member::birthday),
    std::make_pair(&MemberDTO::status, &db::member::status));
};

// mapping
template <typename MemberRow> struct ReflectTableRow<MemberDTO, MemberRow> {
  static MemberDTO assign_model(MemberRow&& row)
  {
    return MemberDTO{.id = row.id,
                     .member_id = row.member_id,
                     .user_rk_id = row.user_rk_id,
                     .registration_date = row.registration_date,
                     .level_rk_id = row.level_rk_id,
                     .points = row.points,
                     .gender = row.gender,
                     .birthday = row.birthday,
                     .status = row.status};
  }
};
}  // namespace model
