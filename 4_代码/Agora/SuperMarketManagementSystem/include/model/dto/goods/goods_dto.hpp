#pragma once
// stl
#include <iostream>
#include <string>
// third_party
#include <nlohmann/json.hpp>
// table
#include <model/db/common/unit.h>
#include <model/db/goods/goods.h>
#include <model/db/goods/goods_category.h>
#include <model/db/goods/inventory.h>
#include <model/db/warehouse/warehouse.h>
// tools
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>

// CREATE TABLE goods (
//     id INTEGER PRIMARY KEY AUTOINCREMENT,
//     goods_id TEXT UNIQUE NOT NULL,
//     category_id INTEGER,
//     supplier_id INTEGER,
//     unit_id INTEGER,
//     goods_name TEXT NOT NULL,
//     shelf_life_days INTEGER,
//     barcode TEXT,
//     image_url TEXT,
//     description TEXT,
//     FOREIGN KEY (category_id) REFERENCES category(id),
//     FOREIGN KEY (unit_id) REFERENCES unit(id)
// );
//

struct GoodsDTO {
  id_type id;
  std::string goods_id;
  id_type category_rk_id;
  id_type supplier_rk_id;
  id_type unit_rk_id;
  std::string goods_name;
  date_cnt_type shelf_life_days;
  std::string barcode;
  std::string image_url;
  std::string description;

  static GoodsDTO from_json(const nlohmann::json &j) {
    try {
      return GoodsDTO{.id = 0,
                      .goods_id = j.at("goods_id").get<std::string>(),
                      .category_rk_id = j.at("category_rk_id").get<id_type>(),
                      .supplier_rk_id = j.at("supplier_rk_id").get<id_type>(),
                      .unit_rk_id = j.at("unit_rk_id").get<id_type>(),
                      .goods_name = j.at("goods_name").get<std::string>(),
                      .shelf_life_days = j.at("shelf_life_days").get<id_type>(),
                      .barcode = j.at("barcode").get<std::string>(),
                      .image_url = j.value("image_url", ""),
                      .description = j.at("description").get<std::string>()};
    } catch (const std::exception &e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

inline void to_json(nlohmann::json &j, const GoodsDTO &goods_dto) {
  j = nlohmann::json{{"goods_id", goods_dto.goods_id},
                     {"category_rk_id", goods_dto.category_rk_id},
                     {"supplier_rk_id", goods_dto.supplier_rk_id},
                     {"unit_rk_id", goods_dto.unit_rk_id},
                     {"goods_name", goods_dto.goods_name},
                     {"shelf_life_days", goods_dto.shelf_life_days},
                     {"barcode", goods_dto.barcode},
                     {"image_url", goods_dto.image_url},
                     {"description", goods_dto.description}};
}

namespace model {

// 反射 DTO 与表字段的映射关系
template <> struct ReflectTable<GoodsDTO, db::goods> {
  static constexpr auto map_members = std::make_tuple(
      std::make_pair(&GoodsDTO::id, &db::goods::id),
      std::make_pair(&GoodsDTO::goods_id, &db::goods::goods_id),
      std::make_pair(&GoodsDTO::category_rk_id, &db::goods::category_rk_id),
      std::make_pair(&GoodsDTO::supplier_rk_id, &db::goods::supplier_rk_id),
      std::make_pair(&GoodsDTO::unit_rk_id, &db::goods::unit_rk_id),
      std::make_pair(&GoodsDTO::goods_name, &db::goods::goods_name),
      std::make_pair(&GoodsDTO::shelf_life_days, &db::goods::shelf_life_days),
      std::make_pair(&GoodsDTO::barcode, &db::goods::barcode),
      std::make_pair(&GoodsDTO::image_url, &db::goods::image_url),
      std::make_pair(&GoodsDTO::description, &db::goods::description));
};

// 如果你还需要从数据库行反射回 DTO，可以添加如下内容：
template <typename GoodsRow> struct ReflectTableRow<GoodsDTO, GoodsRow> {
  static GoodsDTO assign_model(GoodsRow &&row) {
    return GoodsDTO{.goods_id = row.goods_id,
                    .category_rk_id = row.category_rk_id,
                    .supplier_rk_id = row.supplier_rk_id,
                    .unit_rk_id = row.unit_rk_id,
                    .goods_name = row.goods_name,
                    .shelf_life_days = row.shelf_life_days,
                    .barcode = row.barcode,
                    .image_url = row.image_url,
                    .description = row.description};
  }
};

} // namespace model

struct GoodsDetailInfo {
  std::string goods_id;
  std::string goods_name;
  date_cnt_type shelf_life_days;
  std::string unit;
  id_type quantity;
  std::string warehouse_id;
  std::string warehouse_name;
  std::string location;
  std::string category;
};

inline void to_json(nlohmann::json &j, const GoodsDetailInfo &info) {
  j = nlohmann::json{{"goods_id", info.goods_id},
                     {"goods_name", info.goods_name},
                     {"shelf_life_days", info.shelf_life_days},
                     {"unit", info.unit},
                     {"quantity", info.quantity},
                     {"warehouse_id", info.warehouse_id},
                     {"warehouse_name", info.warehouse_name},
                     {"location", info.location},
                     {"category", info.category}};
}
