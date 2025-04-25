#pragma once
#include <common/common_utils.hpp>
#include <common/database_utils.hpp>
#include <common/uni_define.h>
#include <sqlpp11/chrono.h>
#include <sqlpp11/data_types.h>
#include <sqlpp11/insert.h>
#include <sqlpp11/select.h>
#include <sqlpp11/sqlpp11.h>

namespace model {
namespace details {

template <typename Reflect, typename Model, typename Table, size_t... Is>
auto assign_table_impl(Model &&model, Table &&table,
                       std::index_sequence<Is...>) {
  return std::make_tuple(
      (std::forward<Table>(table).*std::get<Is>(Reflect::map_members).second =
           std::forward<Model>(model).*
           std::get<Is>(Reflect::map_members).first)...);
}

// 增强类型安全的assign_table入口
template <typename Reflect, typename Model, typename Table, size_t Start = 0>
auto assign_table(Model &&model, Table &&table) {
  constexpr auto size = std::tuple_size_v<decltype(Reflect::map_members)>;
  static_assert(Start <= size, "Start index out of range");
  return details::assign_table_impl<Reflect>(
      std::forward<Model>(model), std::forward<Table>(table),
      std::make_index_sequence<size - Start>{});
}
} // namespace details

template <typename Model, typename Table> struct ReflectTable;

template <typename Model, typename TableRow> struct ReflectTableRow {};

template <typename Reflect, typename Model, typename Table, size_t Start = 1>
auto assign_table(Model &&model, Table &&table) {
  constexpr auto size = std::tuple_size_v<decltype(Reflect::map_members)>;
  return details::assign_table_impl<Reflect>(
      std::forward<Model>(model), std::forward<Table>(table),
      utils::make_index_sequence_from<Start, size - Start>());
}

template <typename Model, typename Table, size_t Start = 1> class GenericModel {
  using pooled_conn_ptr_type =
      std::shared_ptr<sqlpp::sqlite3::pooled_connection>;
  using Reflect = ReflectTable<Model, Table>;

public:
  template <typename T> static insert_ret_type _insert(T &&model) {
    return utils::DataBaseHelper::execute<insert_ret_type>(
        [](const pooled_conn_ptr_type &conn, T &&model_) {
          Table table_{};
          (*conn)(
              insert_into(table_).set(assign_table<Reflect, T, Table, Start>(
                  std::forward<T>(model_), std::forward<Table>(table_))));
          return true;
        },
        std::forward<T>(model));
  }

  template <typename T, typename Condition>
  static update_ret_type _update(T &&model, Condition &&condition) {
    return utils::DataBaseHelper::execute<update_ret_type>(
        [](const pooled_conn_ptr_type &conn_, T &&model_,
           Condition &&condition_) {
          Table table_{};
          (*conn_)(
              sqlpp::update(table_)
                  .set(assign_table<Reflect, T, Table, Start>(
                      std::forward<T>(model_), std::forward<Table>(table_)))
                  .where(std::forward<Condition>(condition_)));
          return true;
        },
        std::forward<T>(model), std::forward<Condition>(condition));
  }

  template <typename Condition>
  static select_ret_type<Model> _select(Condition &&condition) {
    return utils::DataBaseHelper::execute<select_ret_type<Model>>(
        [](const pooled_conn_ptr_type &conn_, Condition &&condition_) {
          Table table_{};
          select_ret_type<Model> ret_container{};
          auto select_result =
              (*conn_)(sqlpp::select(all_of(table_))
                           .from(table_)
                           .where(std::forward<Condition>(condition_)));
          for (auto &row : select_result) {
            ret_container.push_back(
                ReflectTableRow<Model, decltype(row)>::assign_model(row));
          }
          return ret_container;
        },
        std::forward<Condition>(condition));
  }

  template <typename Condition>
  static select_ret_type<Model>
  _select_from(Condition &&condition, count_type page_size, count_type offset) {
    return utils::DataBaseHelper::execute<select_ret_type<Model>>(
        [limit_ = page_size, offset_ = offset](
            const pooled_conn_ptr_type &conn_, Condition &&condition_) {
          Table table_{};
          select_ret_type<Model> ret_container{};
          auto select_result =
              (*conn_)(sqlpp::select(all_of(table_))
                           .from(table_)
                           .where(std::forward<Condition>(condition_))
                           .limit(limit_)
                           .offset(offset_));
          for (auto &row : select_result) {
            ret_container.push_back(
                ReflectTableRow<Model, decltype(row)>::assign_model(row));
          }
          return ret_container;
        },
        std::forward<Condition>(condition));
  }

  template <typename Condition>
  static delete_ret_type _remove(Condition &&condition) {
    return utils::DataBaseHelper::execute<delete_ret_type>(
        [](const pooled_conn_ptr_type &conn_, Condition &&condition_) {
          Table table_{};
          (*conn_)(
              remove_from(table_).where(std::forward<Condition>(condition_)));
          return true;
        },
        std::forward<Condition>(condition));
  }

  static count_type _count() {
    return utils::DataBaseHelper::execute<count_type>(
        [](const pooled_conn_ptr_type &conn_) {
          Table table_{};
          auto rows = (*conn_)(sqlpp::select(sqlpp::count(table_.id))
                                   .from(table_)
                                   .where(table_.id >= 0));
          return rows.front().count;
        });
  }
};
} // namespace model

namespace unused {
template <typename Reflect, typename Model, typename Table, size_t... Is>
Model assign_model_impl(Table &&table, std::index_sequence<Is...>) {
  Model model;
  ((model.*std::get<Is>(Reflect::map_members).first =
        table.*std::get<Is>(Reflect::map_members).second),
   ...);
  return model;
}

template <typename Reflect, typename Model, typename Table, size_t... Is>
Model assign_model_impl(const Table &table, std::index_sequence<Is...>) {
  Model model;
  ((model.*std::get<Is>(Reflect::map_members).first =
        table.*std::get<Is>(Reflect::map_members).second),
   ...);
  return model;
}

template <typename Reflect, typename Model, typename Table, size_t Start = 1>
Model assign_model(Table &&table) {
  constexpr auto size = std::tuple_size_v<decltype(Reflect::map_members)>;
  return assign_model_impl<Reflect, Model, Table, Start>(
      std::forward<Table>(table));
}

} // namespace unused
