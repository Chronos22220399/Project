#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/cache_func_getter.h>
#include <common/uni_define.h>
#include <model/db/sales/sales_return.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for sales_return table
inline static  const std::vector<std::string>
  required_fields = {
 "return_id", //
  "order_id", //
  "return_time", //
  "reason", //
  "staff_id", //
  "total_refund", //
  "remark", //
  "status" //
};

inline static const std::vector<std::string> status_domain ={
  "pending", //
 'received',//
 'cancelled'//
}


    // JSON serialization/deserialization
    static SalesReturnDTO from_json(const nlohmann::json& j) {
        try {
            return SalesReturnDTO{
                .return_id = j.at("return_id").get<std::string>(),
.order_rk_id = getInternalId ("= sales_order", j.at("order_id").get<ex_id_type>()),
.return_time = utils::string_to_datetime(j.at("return_time").get<std::string>()),
.reason = j.at("reason").get<std::string>(),
.staff_rk_id = getInternalId("employee",j.at("staff_rk_id").get<ex_id_type>()),
.total_refund = j.at("total_refund").get<double>(),
.remark = j.at("remark").get<std::string>(),
.status = j.at("status").get<std::string>(),
            };
        } catch (const std::exception& e) {
            std::cerr << "[from_json error] " << e.what() << "\n"
                      << "Input JSON: " << j.dump(2) << std::endl;
            throw;
        }
    }
    
};

inline void to_json(nlohmann::json &j, const SalesReturnDTO& sales_return_dto) {
    j = nlohmann::json{
        {"id", sales_return_dto.id},
{"return_id", sales_return_dto.return_id},
{"order_id", SalesOrderDTO::getExternalId("sales_order",sales_return_dto.order_rk_id)},
{"return_time", utils::datetime_to_string(sales_return_dto.return_time)},
{"reason", sales_return_dto.reason},
{"staff_id", SalesOrderDTO::getExternalId("employee",sales_return_dto.staff_rk_id)},
{"total_refund", sales_return_dto.total_refund},
{"remark", sales_return_dto.remark},
{"status", sales_return_dto.status}
    };
}

// ORM mapping
namespace model {
template <>
struct ReflectTable<SalesReturnDTO, db::sales_return> {
    static constexpr auto map_members = std::make_tuple(
        std::make_pair(&SalesReturnDTO::id, &db::sales_return::id),
std::make_pair(&SalesReturnDTO::return_id, &db::sales_return::return_id),
std::make_pair(&SalesReturnDTO::order_rk_id, &db::sales_return::order_rk_id),
std::make_pair(&SalesReturnDTO::return_time, &db::sales_return::return_time),
std::make_pair(&SalesReturnDTO::reason, &db::sales_return::reason),
std::make_pair(&SalesReturnDTO::staff_rk_id, &db::sales_return::staff_rk_id),
std::make_pair(&SalesReturnDTO::total_refund, &db::sales_return::total_refund),
std::make_pair(&SalesReturnDTO::remark, &db::sales_return::remark),
std::make_pair(&SalesReturnDTO::status, &db::sales_return::status)
    );
};

// mapping
template <typename Sales_returnRow> struct ReflectTableRow<SalesReturnDTO, Sales_returnRow> {
    static SalesReturnDTO assign_model(Sales_returnRow &&row) {
        return SalesReturnDTO {
            .id = row.id,
.return_id = row.return_id,
.order_rk_id = row.order_rk_id,
.return_time = row.return_time,
.reason = row.reason,
.staff_rk_id = row.staff_rk_id,
.total_refund = row.total_refund,
.remark = row.remark,
.status = row.status
        };           
    }
};
} // namespace model
