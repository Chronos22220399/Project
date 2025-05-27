#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/supplier/purchase_order.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for purchase_order table
struct PurchaseOrderDTO {
  inline static const std::vector<std::string> required_fields = {
    "purchase_order_id",
    "supplier_id",
    "created_at",
    "created_by",
    "expected_arrival_date",
    "actual_arrival_date",
    "status",
    "total_amount",
    "remark"};
  inline static const std::vector<std::string> status_domain = {
    "pending_review", "ordered", "received"};

  in_id_type id = 0;
  std::string purchase_order_id = "";
  in_id_type supplier_rk_id = 0;
  datetime_type created_at = {};
  in_id_type created_by = 0;
  datetime_type expected_arrival_date = {};
  datetime_type actual_arrival_date = {};
  std::string status = "";
  double total_amount = 0.0;
  std::string remark = "";

  // JSON serialization/deserialization
  static PurchaseOrderDTO from_json(const nlohmann::json& j)
  {
    try {
      return PurchaseOrderDTO{
        .purchase_order_id = j.at("purchase_order_id").get<std::string>(),
        .supplier_rk_id =
          getInternalId("myvenv", j.at("supplier_rk_id").get<ex_id_type>()),
        .created_at =
          utils::string_to_datetime(j.at("created_at").get<std::string>()),
        .created_by =
          getInternalId("employee", j.at("created_by").get<ex_id_type>()),
        .expected_arrival_date = utils::string_to_time(
          j.at("expected_arrival_date").get<std::string>()),
        .actual_arrival_date =
          utils::string_to_datetime(j.at("actual_arrival_date").get<std::string>()),
        .status = j.at("status").get<std::string>(),
        .total_amount = j.at("total_amount").get<double>(),
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

inline void to_json(nlohmann::json& j,
                    const PurchaseOrderDTO& purchase_order_dto)
{
  j = nlohmann::json{
    {"id", purchase_order_dto.id},
    {"purchase_order_id", purchase_order_dto.purchase_order_id},
    {"supplier_id", PurchaseOrderDTO::getExternalId(
                      "myvenv", purchase_order_dto.supplier_rk_id)},
    {"created_at", utils::datetime_to_string(purchase_order_dto.created_at)},
    {"created_by", PurchaseOrderDTO::getExternalId(
                     "employee", purchase_order_dto.created_by)},
    {"expected_arrival_date",
     utils::datetime_to_string(purchase_order_dto.expected_arrival_date)},
    {"actual_arrival_date",
     utils::datetime_to_string(purchase_order_dto.actual_arrival_date)},
    {"status", purchase_order_dto.status},
    {"total_amount", purchase_order_dto.total_amount},
    {"remark", purchase_order_dto.remark}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<PurchaseOrderDTO, db::purchase_order> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&PurchaseOrderDTO::id, &db::purchase_order::id),
    std::make_pair(&PurchaseOrderDTO::purchase_order_id,
                   &db::purchase_order::purchase_order_id),
    std::make_pair(&PurchaseOrderDTO::supplier_rk_id,
                   &db::purchase_order::supplier_rk_id),
    std::make_pair(&PurchaseOrderDTO::created_at,
                   &db::purchase_order::created_at),
    std::make_pair(&PurchaseOrderDTO::created_by,
                   &db::purchase_order::created_by),
    std::make_pair(&PurchaseOrderDTO::expected_arrival_date,
                   &db::purchase_order::expected_arrival_date),
    std::make_pair(&PurchaseOrderDTO::status, &db::purchase_order::status),
    std::make_pair(&PurchaseOrderDTO::total_amount,
                   &db::purchase_order::total_amount),
    std::make_pair(&PurchaseOrderDTO::remark, &db::purchase_order::remark));
};

// mapping
template <typename Purchase_orderRow>
struct ReflectTableRow<PurchaseOrderDTO, Purchase_orderRow> {
  static PurchaseOrderDTO assign_model(Purchase_orderRow&& row)
  {
    return PurchaseOrderDTO{.id = row.id,
                            .purchase_order_id = row.purchase_order_id,
                            .supplier_rk_id = row.supplier_rk_id,
                            .created_at = row.created_at,
                            .created_by = row.created_by,
                            .expected_arrival_date = row.expected_arrival_date,
                            .actual_arrival_date = row.actual_arrival_date,
                            .status = row.status,
                            .total_amount = row.total_amount,
                            .remark = row.remark};
  }
};
}  // namespace model
