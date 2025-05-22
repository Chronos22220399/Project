#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/global_id_cache.hpp>
#include <common/id_getter.h>
#include <common/uni_define.h>
#include <model/db/warehouse/stock_in.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for stock_in table
struct StockInDTO : public IdGetter {
  inline static const std::vector<std::string> required_fields = {
    "stock_in_id",   // 入库单号（唯一）
    "warehouse_id",  // 仓库ID
    "created_by",    // 创建人ID
    "source_type",   // 来源类型(purchase/transfer/return/other)
    "remark"         // 备注
  };

  inline static const std::vector<std::string> type_domain = {
    "purchase",  // 采购
    "transfer",  // 调拨
    "return",    // 退货
    "other"      // 其他
  };


  in_id_type id = 0;
  ex_id_type stock_in_id = "";
  in_id_type warehouse_rk_id = 0;
  datetime_type created_at = {};
  in_id_type created_by = 0;
  std::string source_type = "";
  in_id_type source_reference = 0;
  remark_type remark = "";

  // JSON serialization/deserialization
  static StockInDTO from_json(const nlohmann::json& j)
  {
    try {
      return StockInDTO{
        .stock_in_id = j.at("stock_in_id").get<std::string>(),
        .warehouse_rk_id =
          getInternalId("warehouse", j.at("warehouse_id").get<ex_id_type>()),
        .created_by =
          getInternalId("employee", j.at("created_by").get<ex_id_type>()),
        .source_type = j.at("source_type").get<std::string>(),
        // .source_reference = 0,
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

inline void to_json(nlohmann::json& j, const StockInDTO& stock_in_dto)
{
  j = nlohmann::json{
    {"stock_in_id", stock_in_dto.stock_in_id},
    {"warehouse_id",
     stock_in_dto.getExternalId("warehouse", stock_in_dto.warehouse_rk_id)},
    {"created_at", utils::time_to_string(stock_in_dto.created_at)},
    {"created_by",
     stock_in_dto.getExternalId("employee", stock_in_dto.created_by)},
    {"source_type", stock_in_dto.source_type},
    // {"source_reference", stock_in_dto.source_reference},
    {"remark", stock_in_dto.remark}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<StockInDTO, db::stock_in> {
  static constexpr auto map_members = std::make_tuple(
    std::make_pair(&StockInDTO::id, &db::stock_in::id),
    std::make_pair(&StockInDTO::stock_in_id, &db::stock_in::stock_in_id),
    std::make_pair(&StockInDTO::warehouse_rk_id,
                   &db::stock_in::warehouse_rk_id),
    std::make_pair(&StockInDTO::created_at, &db::stock_in::created_at),
    std::make_pair(&StockInDTO::created_by, &db::stock_in::created_by),
    std::make_pair(&StockInDTO::source_type, &db::stock_in::source_type),
    std::make_pair(&StockInDTO::source_reference,
                   &db::stock_in::source_reference),
    std::make_pair(&StockInDTO::remark, &db::stock_in::remark));
};

// mapping
template <typename Stock_inRow>
struct ReflectTableRow<StockInDTO, Stock_inRow> {
  static StockInDTO assign_model(Stock_inRow&& row)
  {
    return StockInDTO{.id = row.id,
                      .stock_in_id = row.stock_in_id,
                      .warehouse_rk_id = row.warehouse_rk_id,
                      .created_at = row.created_at,
                      .created_by = row.created_by,
                      .source_type = row.source_type,
                      .source_reference = row.source_reference,
                      .remark = row.remark};
  }
};
}  // namespace model
