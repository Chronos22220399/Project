#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/cache_func_getter.h>
#include <common/uni_define.h>
#include <model/db/member/member_purchase_record.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for member_purchase_record table
struct MemberPurchaseRecordDTO: public CacheFuncGetter {
    inline static const std::vector<std::string> required_fields = Ellipsis;
    inline static const std::vector<std::string> _domain = Ellipsis;

    in_id_type id = 0;
std::string record_id = "";
in_id_type member_rk_id = 0;
datetime_type transaction_date = {};
double amount = 0.0;
in_id_type earned_points = 0;

    // JSON serialization/deserialization
    static MemberPurchaseRecordDTO from_json(const nlohmann::json& j) {
        try {
            return MemberPurchaseRecordDTO{
                .record_id = j.at("record_id").get<std::string>(),
.member_rk_id = j.at("member_rk_id").get<in_id_type>(),
.transaction_date = utils::string_to_time(j.at("transaction_date").get<std::string>()),
.amount = j.at("amount").get<double>(),
.earned_points = j.at("earned_points").get<in_id_type>(),
            };
        } catch (const std::exception& e) {
            std::cerr << "[from_json error] " << e.what() << "\n"
                      << "Input JSON: " << j.dump(2) << std::endl;
            throw;
        }
    }
    
};

inline void to_json(nlohmann::json &j, const MemberPurchaseRecordDTO& member_purchase_record_dto) {
    j = nlohmann::json{
        {"id", member_purchase_record_dto.id},
{"record_id", member_purchase_record_dto.record_id},
{"member_rk_id", member_purchase_record_dto.member_rk_id},
{"transaction_date", utils::time_to_string(member_purchase_record_dto.transaction_date)},
{"amount", member_purchase_record_dto.amount},
{"earned_points", member_purchase_record_dto.earned_points}
    };
}

// ORM mapping
namespace model {
template <>
struct ReflectTable<MemberPurchaseRecordDTO, db::member_purchase_record> {
    static constexpr auto map_members = std::make_tuple(
        std::make_pair(&MemberPurchaseRecordDTO::id, &db::member_purchase_record::id),
std::make_pair(&MemberPurchaseRecordDTO::record_id, &db::member_purchase_record::record_id),
std::make_pair(&MemberPurchaseRecordDTO::member_rk_id, &db::member_purchase_record::member_rk_id),
std::make_pair(&MemberPurchaseRecordDTO::transaction_date, &db::member_purchase_record::transaction_date),
std::make_pair(&MemberPurchaseRecordDTO::amount, &db::member_purchase_record::amount),
std::make_pair(&MemberPurchaseRecordDTO::earned_points, &db::member_purchase_record::earned_points)
    );
};

// mapping
template <typename Member_purchase_recordRow> struct ReflectTableRow<MemberPurchaseRecordDTO, Member_purchase_recordRow> {
    static MemberPurchaseRecordDTO assign_model(Member_purchase_recordRow &&row) {
        return MemberPurchaseRecordDTO {
            .id = row.id,
.record_id = row.record_id,
.member_rk_id = row.member_rk_id,
.transaction_date = row.transaction_date,
.amount = row.amount,
.earned_points = row.earned_points
        };           
    }
};
} // namespace model
