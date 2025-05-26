#pragma once
#include <common/cache_func_getter.h>
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/sales/sales_order.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for sales_order table
struct SalesOrderDTO : public CacheFuncGetter {
  inline static const std::vector<std::string> required_fields = {
    "order_id",       "sale_time",     "cashier_id",
    "member_id",      "total_amount",  "paid_amount",
    "payment_method", "discount_info", "remark"};
  inline static const std::vector<std::string> payment_method_domain = {
    "cash", "bank_card", "wechat", "alipay", "other"};

  in_id_type id = 0;
  std::string order_id = "";
  datetime_type sale_time = {};
  in_id_type cashier_rk_id = 0;
  in_id_type member_rk_id = 0;
  double total_amount = 0.0;
  double paid_amount = 0.0;
  std::string payment_method = "";
  std::string discount_info = "";
  std::string remark = "";

  // JSON serialization/deserialization
  static SalesOrderDTO from_json(const nlohmann::json& j)
  {
    try {
      return SalesOrderDTO{
        .order_id = j.at("order_id").get<std::string>(),
        .sale_time =
          utils::string_to_datetime(j.at("sale_time").get<std::string>()),
        .cashier_rk_id =
          getInternalId("employee", j.at("cashier_id").get<ex_id_type>()),
        .member_rk_id =
          getInternalId("member", j.at("member_id").get<ex_id_type>()),
        .total_amount = j.at("total_amount").get<double>(),
        .paid_amount = j.at("paid_amount").get<double>(),
        .payment_method = j.at("payment_method").get<std::string>(),
        .discount_info = j.at("discount_info").get<std::string>(),
        .remark = j.at("remark").get<std::string>(),
      };
    }
    catch (const std::exception& e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json& j, const SalesOrderDTO& sales_order_dto)
{
  j = nlohmann::json{
    {"id", sales_order_dto.id},
    {"order_id", sales_order_dto.order_id},
    {"sale_time", utils::datetime_to_string(sales_order_dto.sale_time)},
    {"cashier_id",
     SalesOrderDTO::getExternalId("employee", sales_order_dto.cashier_rk_id)},
    {"member_id",
     SalesOrderDTO::getExternalId("member", sales_order_dto.member_rk_id)},
    {"total_amount", sales_order_dto.total_amount},
    {"paid_amount", sales_order_dto.paid_amount},
    {"payment_method", sales_order_dto.payment_method},
    {"payment_method", sales_order_dto.payment_method},
    {"discount_info", sales_order_dto.discount_info},
    {"remark", sales_order_dto.remark}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<SalesOrderDTO, db::sales_order> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&SalesOrderDTO::id, &db::sales_order::id),
    std::make_pair(&SalesOrderDTO::order_id, &db::sales_order::order_id),
    std::make_pair(&SalesOrderDTO::sale_time, &db::sales_order::sale_time),
    std::make_pair(&SalesOrderDTO::cashier_rk_id,
                   &db::sales_order::cashier_rk_id),
    std::make_pair(&SalesOrderDTO::member_rk_id,
                   &db::sales_order::member_rk_id),
    std::make_pair(&SalesOrderDTO::total_amount,
                   &db::sales_order::total_amount),
    std::make_pair(&SalesOrderDTO::paid_amount, &db::sales_order::paid_amount),
    std::make_pair(&SalesOrderDTO::payment_method,
                   &db::sales_order::payment_method),
    std::make_pair(&SalesOrderDTO::discount_info,
                   &db::sales_order::discount_info),
    std::make_pair(&SalesOrderDTO::remark, &db::sales_order::remark));
};

// mapping
template <typename Sales_orderRow>
struct ReflectTableRow<SalesOrderDTO, Sales_orderRow> {
  static SalesOrderDTO assign_model(Sales_orderRow&& row)
  {
    return SalesOrderDTO{.id = row.id,
                         .order_id = row.order_id,
                         .sale_time = row.sale_time,
                         .cashier_rk_id = row.cashier_rk_id,
                         .member_rk_id = row.member_rk_id,
                         .total_amount = row.total_amount,
                         .paid_amount = row.paid_amount,
                         .payment_method = row.payment_method,
                         .discount_info = row.discount_info,
                         .remark = row.remark};
  }
};
}  // namespace model
