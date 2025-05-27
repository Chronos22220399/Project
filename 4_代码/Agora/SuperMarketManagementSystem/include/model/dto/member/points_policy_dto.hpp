#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/cache_func_getter.h>
#include <common/uni_define.h>
#include <model/db/member/points_policy.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for points_policy table
struct PointsPolicyDTO: public CacheFuncGetter {
    inline static const std::vector<std::string> required_fields = Ellipsis;
    inline static const std::vector<std::string> _domain = Ellipsis;

    in_id_type id = 0;
std::string policy_id = "";
std::string policy_name = "";
double point_per_yuan = 0.0;
std::string description = "";
datetime_type effective_from = {};
datetime_type effective_to = {};
std::string effective_to = "";
std::string OR = "";

    // JSON serialization/deserialization
    static PointsPolicyDTO from_json(const nlohmann::json& j) {
        try {
            return PointsPolicyDTO{
                .policy_id = j.at("policy_id").get<std::string>(),
.policy_name = j.at("policy_name").get<std::string>(),
.point_per_yuan = j.at("point_per_yuan").get<double>(),
.description = j.at("description").get<std::string>(),
.effective_from = utils::string_to_time(j.at("effective_from").get<std::string>()),
.effective_to = utils::string_to_time(j.at("effective_to").get<std::string>()),
.effective_to = j.at("effective_to").get<std::string>(),
.OR = j.at("OR").get<std::string>(),
            };
        } catch (const std::exception& e) {
            std::cerr << "[from_json error] " << e.what() << "\n"
                      << "Input JSON: " << j.dump(2) << std::endl;
            throw;
        }
    }
    
};

inline void to_json(nlohmann::json &j, const PointsPolicyDTO& points_policy_dto) {
    j = nlohmann::json{
        {"id", points_policy_dto.id},
{"policy_id", points_policy_dto.policy_id},
{"policy_name", points_policy_dto.policy_name},
{"point_per_yuan", points_policy_dto.point_per_yuan},
{"description", points_policy_dto.description},
{"effective_from", utils::time_to_string(points_policy_dto.effective_from)},
{"effective_to", utils::time_to_string(points_policy_dto.effective_to)},
{"effective_to", points_policy_dto.effective_to},
{"OR", points_policy_dto.OR}
    };
}

// ORM mapping
namespace model {
template <>
struct ReflectTable<PointsPolicyDTO, db::points_policy> {
    static constexpr auto map_members = std::make_tuple(
        std::make_pair(&PointsPolicyDTO::id, &db::points_policy::id),
std::make_pair(&PointsPolicyDTO::policy_id, &db::points_policy::policy_id),
std::make_pair(&PointsPolicyDTO::policy_name, &db::points_policy::policy_name),
std::make_pair(&PointsPolicyDTO::point_per_yuan, &db::points_policy::point_per_yuan),
std::make_pair(&PointsPolicyDTO::description, &db::points_policy::description),
std::make_pair(&PointsPolicyDTO::effective_from, &db::points_policy::effective_from),
std::make_pair(&PointsPolicyDTO::effective_to, &db::points_policy::effective_to),
std::make_pair(&PointsPolicyDTO::effective_to, &db::points_policy::effective_to),
std::make_pair(&PointsPolicyDTO::OR, &db::points_policy::OR)
    );
};

// mapping
template <typename Points_policyRow> struct ReflectTableRow<PointsPolicyDTO, Points_policyRow> {
    static PointsPolicyDTO assign_model(Points_policyRow &&row) {
        return PointsPolicyDTO {
            .id = row.id,
.policy_id = row.policy_id,
.policy_name = row.policy_name,
.point_per_yuan = row.point_per_yuan,
.description = row.description,
.effective_from = row.effective_from,
.effective_to = row.effective_to,
.effective_to = row.effective_to,
.OR = row.OR
        };           
    }
};
} // namespace model
