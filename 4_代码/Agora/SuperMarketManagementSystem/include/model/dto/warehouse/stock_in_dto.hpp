#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/warehouse/stock_in.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for stock_in table
struct StockInDTO {
    inline static const std::vector<std::string> required_fields = Ellipsis;
    inline static const std::vector<std::string> _domain = Ellipsis;

    in_id_type id = 0;
std::string stock_in_id = "";
in_id_type warehouse_rk_id = 0;
datetime_type created_at = {};
in_id_type created_by = 0;
std::string source_type = "";
std::string source_type = "";
in_id_type source_reference = 0;
std::string remark = "";

    // JSON serialization/deserialization
    static StockInDTO from_json(const nlohmann::json& j) {
        try {
            return StockInDTO{
                .stock_in_id = j.at("stock_in_id").get<std::string>(),
.warehouse_rk_id = j.at("warehouse_rk_id").get<in_id_type>(),
.created_at = utils::string_to_time(j.at("created_at").get<std::string>()),
.created_by = j.at("created_by").get<in_id_type>(),
.source_type = j.at("source_type").get<std::string>(),
.source_type = j.at("source_type").get<std::string>(),
.source_reference = j.at("source_reference").get<in_id_type>(),
.remark = j.at("remark").get<std::string>(),
            };
        } catch (const std::exception& e) {
            std::cerr << "[from_json error] " << e.what() << "\n"
                      << "Input JSON: " << j.dump(2) << std::endl;
            throw;
        }
    }
    
};

inline void to_json(nlohmann::json &j, const StockInDTO& stock_in_dto) {
    j = nlohmann::json{
        {"id", stock_in_dto.id},
{"stock_in_id", stock_in_dto.stock_in_id},
{"warehouse_rk_id", stock_in_dto.warehouse_rk_id},
{"created_at", utils::time_to_string(stock_in_dto.created_at)},
{"created_by", stock_in_dto.created_by},
{"source_type", stock_in_dto.source_type},
{"source_type", stock_in_dto.source_type},
{"source_reference", stock_in_dto.source_reference},
{"remark", stock_in_dto.remark}
    };
}

// ORM mapping
namespace model {
template <>
struct ReflectTable<StockInDTO, db::stock_in> {
    static constexpr auto map_members = std::make_tuple(
        std::make_pair(&StockInDTO::id, &db::stock_in::id),
std::make_pair(&StockInDTO::stock_in_id, &db::stock_in::stock_in_id),
std::make_pair(&StockInDTO::warehouse_rk_id, &db::stock_in::warehouse_rk_id),
std::make_pair(&StockInDTO::created_at, &db::stock_in::created_at),
std::make_pair(&StockInDTO::created_by, &db::stock_in::created_by),
std::make_pair(&StockInDTO::source_type, &db::stock_in::source_type),
std::make_pair(&StockInDTO::source_type, &db::stock_in::source_type),
std::make_pair(&StockInDTO::source_reference, &db::stock_in::source_reference),
std::make_pair(&StockInDTO::remark, &db::stock_in::remark)
    );
};

// mapping
template <typename Stock_inRow> struct ReflectTableRow<StockInDTO, Stock_inRow> {
    static StockInDTO assign_model(Stock_inRow &&row) {
        return StockInDTO {
            .id = row.id,
.stock_in_id = row.stock_in_id,
.warehouse_rk_id = row.warehouse_rk_id,
.created_at = row.created_at,
.created_by = row.created_by,
.source_type = row.source_type,
.source_type = row.source_type,
.source_reference = row.source_reference,
.remark = row.remark
        };           
    }
};
} // namespace model
