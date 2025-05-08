#pragma once
#include <common/common_utils.hpp>
#include <common/generic_model.hpp>
#include <common/uni_define.h>
#include <iostream>
#include <model/db/goods/goods_category.h>
#include <nlohmann/json.hpp>
#include <string>

// -- 商品类别表（支持层级结构）
// CREATE TABLE IF NOT EXISTS category (
//     id INTEGER PRIMARY KEY AUTOINCREMENT,
//     category_id TEXT UNIQUE,
//     category_name TEXT NOT NULL,
//     category_description TEXT,
//     parent_category_id INTEGER DEFAULT NULL,
//     FOREIGN KEY (parent_category_id) REFERENCES category(id)
// );

// GoodsCategoryDTO 对应 category 表
struct GoodsCategoryDTO {
  in_id_type id;
  std::string goods_category_id;
  std::string goods_category_name;
  std::string goods_category_description;
  in_id_type parent_category_id = 0; // 0 表示 NULL

  // 从 JSON 中反序列化 GoodsCategoryDTO
  static GoodsCategoryDTO from_json(const nlohmann::json &j) {
    try {
      return GoodsCategoryDTO{
          .id = 0, // 使用默认的 id，可以根据需求调整
          .goods_category_id = j.at("goods_category_id").get<std::string>(),
          .goods_category_name = j.at("goods_category_name").get<std::string>(),
          .goods_category_description =
              j.value("goods_category_description", ""), // 默认值为空字符串
          .parent_category_id = j.at("parent_category_id").get<in_id_type>()};
    } catch (const std::exception &e) {
      std::cerr << "[from_json error] " << e.what() << "\n"
                << "Input JSON: " << j.dump(2) << std::endl;
      throw;
    }
  }
};

// 将 GoodsCategoryDTO 对象序列化为 JSON
inline void to_json(nlohmann::json &j, const GoodsCategoryDTO &gc) {
  j = nlohmann::json{
      {"goods_category_id", gc.goods_category_id},
      {"goods_category_name", gc.goods_category_name},
      {"goods_category_description", gc.goods_category_description},
      {"goods_parent_category_id", gc.parent_category_id}};
}

// 反射映射 GoodsCategoryDTO 和 db::category 表字段
namespace model {
template <> struct ReflectTable<GoodsCategoryDTO, db::goods_category> {
  static constexpr auto map_members = std::make_tuple(
      std::make_pair(&GoodsCategoryDTO::id, &db::goods_category::id),
      std::make_pair(&GoodsCategoryDTO::goods_category_id,
                     &db::goods_category::goods_category_id),
      std::make_pair(&GoodsCategoryDTO::goods_category_name,
                     &db::goods_category::goods_category_name),
      std::make_pair(&GoodsCategoryDTO::goods_category_description,
                     &db::goods_category::goods_category_description),
      std::make_pair(&GoodsCategoryDTO::parent_category_id,
                     &db::goods_category::parent_category_id));
};

// 从数据库行映射回 GoodsCategoryDTO
template <typename CategoryRow>
struct ReflectTableRow<GoodsCategoryDTO, CategoryRow> {
  static GoodsCategoryDTO assign_model(CategoryRow &&row) {
    return GoodsCategoryDTO{.goods_category_id = row.goods_category_id,
                            .goods_category_name =
                                std::string(row.goods_category_name),
                            .goods_category_description =
                                std::string(row.goods_category_description),
                            .parent_category_id = row.parent_category_id};
  }
};
} // namespace model
