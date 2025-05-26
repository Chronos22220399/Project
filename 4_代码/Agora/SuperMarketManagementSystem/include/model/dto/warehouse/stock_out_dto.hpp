#pragma once
#include <common/cache_func_getter.h>
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/warehouse/stock_out.h>
#include <nlohmann/json.hpp>
#include <sqlpp11/sqlpp11.h>
#include <string>

// DTO for stock_out table
struct StockOutDTO : public CacheFuncGetter {
  inline static const std::vector<std::string> required_fields = {
    "stock_out_id",      //
    "warehouse_id",      //
    "created_by",        //
    "destination_type",  //
    // "destination_reference",  //
    "status",  //
    "remark"   //
  };

  inline static const std::vector<std::string> destination_type_domain = {
    "sale",      //
    "transfer",  //
    "scrap",     //
    "other"      //
  };

  inline static const std::vector<std::string> status_domain = {
    "pending",    //
    "completed",  //
    "cancelled"   //
  };

  in_id_type id = 0;
  std::string stock_out_id = "";
  in_id_type warehouse_rk_id = 0;
  datetime_type created_at = {};
  in_id_type created_by = 0;
  std::string destination_type = "";
  in_id_type destination_reference = 0;
  std::string status = "";
  std::string remark = "";

  // JSON serialization/deserialization
  static StockOutDTO from_json(const nlohmann::json& j)
  {
    try {
      return StockOutDTO{
        .stock_out_id = j.at("stock_out_id").get<std::string>(),
        .warehouse_rk_id =
          getInternalId("warehouse", j.at("warehouse_id").get<ex_id_type>()),
        .created_by =
          getInternalId("employee", j.at("created_by").get<ex_id_type>()),
        .destination_type = j.at("destination_type").get<std::string>(),
        // .destination_reference =
        //   j.at("destination_reference").get<in_id_type>(),
        .status = j.at("status").get<std::string>(),
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

inline void to_json(nlohmann::json& j, const StockOutDTO& stock_out_dto)
{
  j = nlohmann::json{
    {"stock_out_id", stock_out_dto.stock_out_id},
    {"warehouse_id",
     StockOutDTO::getExternalId("warehouse", stock_out_dto.warehouse_rk_id)},
    {"created_at", utils::datetime_to_string(stock_out_dto.created_at)},
    {"created_by",
     StockOutDTO::getExternalId("employee", stock_out_dto.created_by)},
    {"destination_type", stock_out_dto.destination_type},
    // {"destination_reference", stock_out_dto.destination_reference},
    {"status", stock_out_dto.status},
    {"remark", stock_out_dto.remark}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<StockOutDTO, db::stock_out> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&StockOutDTO::id, &db::stock_out::id),
    std::make_pair(&StockOutDTO::stock_out_id, &db::stock_out::stock_out_id),
    std::make_pair(&StockOutDTO::warehouse_rk_id,
                   &db::stock_out::warehouse_rk_id),
    std::make_pair(&StockOutDTO::created_at, &db::stock_out::created_at),
    std::make_pair(&StockOutDTO::created_by, &db::stock_out::created_by),
    std::make_pair(&StockOutDTO::destination_type,
                   &db::stock_out::destination_type),
    std::make_pair(&StockOutDTO::destination_reference,
                   &db::stock_out::destination_reference),
    std::make_pair(&StockOutDTO::status, &db::stock_out::status),
    std::make_pair(&StockOutDTO::remark, &db::stock_out::remark));
};

// mapping
template <typename Stock_outRow>
struct ReflectTableRow<StockOutDTO, Stock_outRow> {
  static StockOutDTO assign_model(Stock_outRow&& row)
  {
    return StockOutDTO{.id = row.id,
                       .stock_out_id = row.stock_out_id,
                       .warehouse_rk_id = row.warehouse_rk_id,
                       .created_at = row.created_at,
                       .created_by = row.created_by,
                       .destination_type = row.destination_type,
                       .destination_reference = row.destination_reference,
                       .status = row.status,
                       .remark = row.remark};
  }
};
}  // namespace model
