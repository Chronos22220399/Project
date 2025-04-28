#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <model/db/goods/goods_promotion.h>
#include <nlohmann/json.hpp>
#include <string>

// DTO for goods_promotion table
struct GoodsPromotionDTO {
  id_type id = 0;
  id_type goods_rk_id = 0;
  id_type promotion_rk_id = 0;
  double discount_rate = 0.0;
  double full_threshold = 0.0;
  double reduce_amount = 0.0;
  id_type buy_quantity = 0;
  std::string gift_product = "";

  // JSON serialization/deserialization
  static GoodsPromotionDTO from_json(const nlohmann::json &j) {
    try {
      return GoodsPromotionDTO{
          .goods_rk_id = j.at("goods_rk_id").get<id_type>(),
          .promotion_rk_id = j.at("promotion_id").get<id_type>(),
          .discount_rate = j.at("discount_rate").get<double>(),
          .full_threshold = j.at("full_threshold").get<double>(),
          .reduce_amount = j.at("reduce_amount").get<double>(),
          .buy_quantity = j.at("buy_quantity").get<id_type>(),
          .gift_product = j.at("gift_product").get<std::string>(),
      };
    } catch (const std::exception &e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json &j,
                    const GoodsPromotionDTO &goods_promotion_dto) {
  j = nlohmann::json{{"goods_rk_id", goods_promotion_dto.goods_rk_id},
                     {"promotion_rk_id", goods_promotion_dto.promotion_rk_id},
                     {"discount_rate", goods_promotion_dto.discount_rate},
                     {"full_threshold", goods_promotion_dto.full_threshold},
                     {"reduce_amount", goods_promotion_dto.reduce_amount},
                     {"buy_quantity", goods_promotion_dto.buy_quantity},
                     {"gift_product", goods_promotion_dto.gift_product}};
}

// ORM mapping
namespace model {
template <> struct ReflectTable<GoodsPromotionDTO, db::goods_promotion> {
  static constexpr auto map_members = std::make_tuple(
      std::make_pair(&GoodsPromotionDTO::id, &db::goods_promotion::id),
      std::make_pair(&GoodsPromotionDTO::goods_rk_id,
                     &db::goods_promotion::goods_rk_id),
      std::make_pair(&GoodsPromotionDTO::promotion_rk_id,
                     &db::goods_promotion::promotion_rk_id),
      std::make_pair(&GoodsPromotionDTO::discount_rate,
                     &db::goods_promotion::discount_rate),
      std::make_pair(&GoodsPromotionDTO::full_threshold,
                     &db::goods_promotion::full_threshold),
      std::make_pair(&GoodsPromotionDTO::reduce_amount,
                     &db::goods_promotion::reduce_amount),
      std::make_pair(&GoodsPromotionDTO::buy_quantity,
                     &db::goods_promotion::buy_quantity),
      std::make_pair(&GoodsPromotionDTO::gift_product,
                     &db::goods_promotion::gift_product));
};

// mapping
template <typename Goods_promotionRow>
struct ReflectTableRow<GoodsPromotionDTO, Goods_promotionRow> {
  static GoodsPromotionDTO assign_model(Goods_promotionRow &&row) {
    return GoodsPromotionDTO{.id = row.id,
                             .goods_rk_id = row.goods_rk_id,
                             .promotion_rk_id = row.promotion_rk_id,
                             .discount_rate = row.discount_rate,
                             .full_threshold = row.full_threshold,
                             .reduce_amount = row.reduce_amount,
                             .buy_quantity = row.buy_quantity,
                             .gift_product = row.gift_product};
  }
};
} // namespace model
