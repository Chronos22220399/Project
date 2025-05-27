#pragma once
#include <common/cache_func_getter.h>
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/member/member_level.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for member_level table
struct MemberLevelDTO : public CacheFuncGetter {
  inline static const std::vector<std::string> required_fields = {
    "level_id",     //
    "level_name",   //
    "min_points",   //
    "discout_rate"  //
  };

  in_id_type id = 0;
  ex_id_type level_id = "";
  std::string level_name = "";
  double min_points = 0.0;
  double discount_rate = 0.0;

  // JSON serialization/deserialization
  static MemberLevelDTO from_json(const nlohmann::json& j)
  {
    try {
      return MemberLevelDTO{
        .level_id = j.at("level_id").get<ex_id_type>(),
        .level_name = j.at("level_name").get<std::string>(),
        .min_points = j.at("min_points").get<double>(),
        .discount_rate = j.at("discount_rate").get<double>(),
      };
    }
    catch (const std::exception& e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json& j, const MemberLevelDTO& member_level_dto)
{
  j = nlohmann::json{{"level_id", member_level_dto.level_id},
                     {"level_name", member_level_dto.level_name},
                     {"min_points", member_level_dto.min_points},
                     {"discount_rate", member_level_dto.discount_rate}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<MemberLevelDTO, db::member_level> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&MemberLevelDTO::id, &db::member_level::id),
    std::make_pair(&MemberLevelDTO::level_id, &db::member_level::level_id),
    std::make_pair(&MemberLevelDTO::level_name, &db::member_level::level_name),
    std::make_pair(&MemberLevelDTO::min_points, &db::member_level::min_points),
    std::make_pair(&MemberLevelDTO::discount_rate,
                   &db::member_level::discount_rate));
};

// mapping
template <typename Member_levelRow>
struct ReflectTableRow<MemberLevelDTO, Member_levelRow> {
  static MemberLevelDTO assign_model(Member_levelRow&& row)
  {
    return MemberLevelDTO{.id = row.id,
                          .level_id = row.level_id,
                          .level_name = row.level_name,
                          .min_points = row.min_points,
                          .discount_rate = row.discount_rate};
  }
};
}  // namespace model
