#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/cache_func_getter.h>
#include <common/uni_define.h>
#include <model/db/member/points_exchange_record.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for points_exchange_record table
struct PointsExchangeRecordDTO: public CacheFuncGetter {
    inline static const std::vector<std::string> required_fields = Ellipsis;
    inline static const std::vector<std::string> _domain = Ellipsis;

    in_id_type id = 0;
std::string record_id = "";
in_id_type member_rk_id = 0;
in_id_type item_rk_id = 0;
in_id_type operator_rk_id = 0;
double points_spent = 0.0;
datetime_type redemption_time = {};

    // JSON serialization/deserialization
    static PointsExchangeRecordDTO from_json(const nlohmann::json& j) {
        try {
            return PointsExchangeRecordDTO{
                .record_id = j.at("record_id").get<std::string>(),
.member_rk_id = j.at("member_rk_id").get<in_id_type>(),
.item_rk_id = j.at("item_rk_id").get<in_id_type>(),
.operator_rk_id = j.at("operator_rk_id").get<in_id_type>(),
.points_spent = j.at("points_spent").get<double>(),
.redemption_time = utils::string_to_time(j.at("redemption_time").get<std::string>()),
            };
        } catch (const std::exception& e) {
            std::cerr << "[from_json error] " << e.what() << "\n"
                      << "Input JSON: " << j.dump(2) << std::endl;
            throw;
        }
    }
    
};

inline void to_json(nlohmann::json &j, const PointsExchangeRecordDTO& points_exchange_record_dto) {
    j = nlohmann::json{
        {"id", points_exchange_record_dto.id},
{"record_id", points_exchange_record_dto.record_id},
{"member_rk_id", points_exchange_record_dto.member_rk_id},
{"item_rk_id", points_exchange_record_dto.item_rk_id},
{"operator_rk_id", points_exchange_record_dto.operator_rk_id},
{"points_spent", points_exchange_record_dto.points_spent},
{"redemption_time", utils::time_to_string(points_exchange_record_dto.redemption_time)}
    };
}

// ORM mapping
namespace model {
template <>
struct ReflectTable<PointsExchangeRecordDTO, db::points_exchange_record> {
    static constexpr auto map_members = std::make_tuple(
        std::make_pair(&PointsExchangeRecordDTO::id, &db::points_exchange_record::id),
std::make_pair(&PointsExchangeRecordDTO::record_id, &db::points_exchange_record::record_id),
std::make_pair(&PointsExchangeRecordDTO::member_rk_id, &db::points_exchange_record::member_rk_id),
std::make_pair(&PointsExchangeRecordDTO::item_rk_id, &db::points_exchange_record::item_rk_id),
std::make_pair(&PointsExchangeRecordDTO::operator_rk_id, &db::points_exchange_record::operator_rk_id),
std::make_pair(&PointsExchangeRecordDTO::points_spent, &db::points_exchange_record::points_spent),
std::make_pair(&PointsExchangeRecordDTO::redemption_time, &db::points_exchange_record::redemption_time)
    );
};

// mapping
template <typename Points_exchange_recordRow> struct ReflectTableRow<PointsExchangeRecordDTO, Points_exchange_recordRow> {
    static PointsExchangeRecordDTO assign_model(Points_exchange_recordRow &&row) {
        return PointsExchangeRecordDTO {
            .id = row.id,
.record_id = row.record_id,
.member_rk_id = row.member_rk_id,
.item_rk_id = row.item_rk_id,
.operator_rk_id = row.operator_rk_id,
.points_spent = row.points_spent,
.redemption_time = row.redemption_time
        };           
    }
};
} // namespace model
