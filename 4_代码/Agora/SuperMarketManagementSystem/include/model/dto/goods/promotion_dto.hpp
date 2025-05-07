#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/goods/promotion.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for promotion table
struct PromotionDTO {
  in_id_type id = 0;
  std::string promotion_id = "";
  std::string promotion_name = "";
  std::string description = "";
  std::string type = "";
  datetime_type start_time = {};
  datetime_type end_time = {};
  std::string status = "";

  // JSON serialization/deserialization
  static PromotionDTO from_json(const nlohmann::json &j) {
    try {
      return PromotionDTO{
          .promotion_id = j.at("promotion_id").get<std::string>(),
          .promotion_name = j.at("promotion_name").get<std::string>(),
          .description = j.at("description").get<std::string>(),
          .type = j.at("type").get<std::string>(),
          .start_time =
              utils::string_to_time(j.at("start_time").get<std::string>()),
          .end_time =
              utils::string_to_time(j.at("end_time").get<std::string>()),
          .status = j.at("status").get<std::string>(),
      };
    } catch (const std::exception &e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json &j, const PromotionDTO &promotion_dto) {
  j = nlohmann::json{
      {"promotion_id", promotion_dto.promotion_id},
      {"promotion_name", promotion_dto.promotion_name},
      {"description", promotion_dto.description},
      {"type", promotion_dto.type},
      {"start_time", utils::time_to_string(promotion_dto.start_time)},
      {"end_time", utils::time_to_string(promotion_dto.end_time)},
      {"status", promotion_dto.status}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<PromotionDTO, db::promotion> {
  static constexpr auto map_members = std::make_tuple(
      std::make_pair(&PromotionDTO::id, &db::promotion::id),
      std::make_pair(&PromotionDTO::promotion_id, &db::promotion::promotion_id),
      std::make_pair(&PromotionDTO::promotion_name,
                     &db::promotion::promotion_name),
      std::make_pair(&PromotionDTO::description, &db::promotion::description),
      std::make_pair(&PromotionDTO::type, &db::promotion::type),
      std::make_pair(&PromotionDTO::start_time, &db::promotion::start_time),
      std::make_pair(&PromotionDTO::end_time, &db::promotion::end_time),
      std::make_pair(&PromotionDTO::status, &db::promotion::status));
};

// mapping
template <typename PromotionRow>
struct ReflectTableRow<PromotionDTO, PromotionRow> {
  static PromotionDTO assign_model(PromotionRow &&row) {
    return PromotionDTO{.id = row.id,
                        .promotion_id = row.promotion_id,
                        .promotion_name = row.promotion_name,
                        .description = row.description,
                        .type = row.type,
                        .start_time = row.start_time,
                        .end_time = row.end_time,
                        .status = row.status};
  }
};
} // namespace model
