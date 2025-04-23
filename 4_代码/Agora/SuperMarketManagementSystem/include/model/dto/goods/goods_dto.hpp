#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <iostream>
#include <model/db/goods/goods.h>
#include <nlohmann/json.hpp>
#include <string>

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
  id_type category_id;
  id_type supplier_id;
  id_type unit_id;
  std::string goods_name;
  date_cnt_type shelf_life_days;
  std::string barcode;
  std::string image_url;
  std::string description;

  static GoodsDTO from_json(const nlohmann::json &j) {
    try {
      return GoodsDTO{.id = 1,
                      .goods_id = utils::create_id(),
                      .category_id = j.at("category_id").get<id_type>(),
                      .supplier_id = j.at("supplier_id").get<id_type>(),
                      .unit_id = j.at("unit_id").get<id_type>(),
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

inline void to_json(nlohmann::json &j, const GoodsDTO &g) {
  j = nlohmann::json{{"id", g.id},
                     {"goods_id", g.goods_id},
                     {"category_id", g.category_id},
                     {"supplier_id", g.supplier_id},
                     {"unit_id", g.unit_id},
                     {"goods_name", g.goods_name},
                     {"shelf_life_days", g.shelf_life_days},
                     {"barcode", g.barcode},
                     {"image_url", g.image_url},
                     {"description", g.description}};
}

namespace model {

// 反射 DTO 与表字段的映射关系
template <> struct ReflectTable<GoodsDTO, db::goods> {
  static constexpr auto map_members = std::make_tuple(
      std::make_pair(&GoodsDTO::id, &db::goods::id),
      std::make_pair(&GoodsDTO::goods_id, &db::goods::goods_id),
      std::make_pair(&GoodsDTO::category_id, &db::goods::category_id),
      std::make_pair(&GoodsDTO::supplier_id, &db::goods::supplier_id),
      std::make_pair(&GoodsDTO::unit_id, &db::goods::unit_id),
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
                    .category_id = row.category_id,
                    .supplier_id = row.supplier_id,
                    .unit_id = row.unit_id,
                    .goods_name = row.goods_name,
                    .shelf_life_days = row.shelf_life_days,
                    .barcode = row.barcode,
                    .image_url = row.image_url,
                    .description = row.description};
  }
};

} // namespace model
