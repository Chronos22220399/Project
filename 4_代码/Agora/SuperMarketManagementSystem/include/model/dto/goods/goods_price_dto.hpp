#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/goods/goods_price.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for goods_price table
struct GoodsPriceDTO {
  id_type id = 0;
  id_type goods_id = 0;
  double price = 0.0;
  std::string start_time = "";
  std::string note = "";

  // JSON serialization/deserialization
  static GoodsPriceDTO from_json(const nlohmann::json &j) {
    try {
      return GoodsPriceDTO{
          .goods_id = j.at("goods_id"),
          .price = j.at("price"),
          .start_time = j.at("start_time"),
          .note = j.at("note"),
      };
    } catch (const std::exception &e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }

  nlohmann::json to_json() const {
    return {{"id", id},
            {"goods_id", goods_id},
            {"price", price},
            {"start_time", start_time},
            {"note", note}};
  }
};

// ORM mapping
namespace model {
template <> struct ReflectTable<GoodsPriceDTO, db::goods_price> {
  static constexpr auto map_members = std::make_tuple(
      std::make_pair(&GoodsPriceDTO::id, &db::goods_price::id),
      std::make_pair(&GoodsPriceDTO::goods_id, &db::goods_price::goods_id),
      std::make_pair(&GoodsPriceDTO::price, &db::goods_price::price),
      std::make_pair(&GoodsPriceDTO::start_time, &db::goods_price::start_time),
      std::make_pair(&GoodsPriceDTO::note, &db::goods_price::note));
};

// mapping
template <typename Goods_priceRow>
struct ReflectTableRow<GoodsPriceDTO, Goods_priceRow> {
  static GoodsPriceDTO assign_model(Goods_priceRow &&row) {
    return GoodsPriceDTO{.id = row.id,
                         .goods_id = row.goods_id,
                         .price = row.price,
                         .start_time = utils::to_string(row.start_time),
                         .note = row.note};
  }
};
} // namespace model
