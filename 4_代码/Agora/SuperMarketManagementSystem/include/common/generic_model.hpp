/**
 * @file generic_model.hpp
 * @brief This file contains the implementation of a generic model class
 *        and related functionalities for database operations.
 *
 * It includes reflection mechanisms for mapping models to database tables
 * and provides CRUD operations with type safety and flexibility.
 *
 * @author Ess
 */

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

/**
 * @brief Assigns values from a model to a table using reflection.
 *
 * @tparam Reflect Reflection type containing mapping information.
 * @tparam Model The model type.
 * @tparam Table The table type.
 * @tparam Is Index sequence for tuple iteration.
 * @param model The model instance.
 * @param table The table instance.
 * @param std::index_sequence<Is...> Index sequence for tuple iteration.
 * @return A tuple of assigned values.
 */
template <typename Reflect, typename Model, typename Table, size_t... Is>
auto assign_table_impl(Model &&model, Table &&table,
                       std::index_sequence<Is...>) {
  return std::make_tuple(
      (std::forward<Table>(table).*std::get<Is>(Reflect::map_members).second =
           std::forward<Model>(model).*
           std::get<Is>(Reflect::map_members).first)...);
}
// File: generic_model.hpp
// Author: [Your Name]
// Date: [Current Date]
// Description: This file contains the implementation of the generic model class
// and related functionalities.

/**
 * @brief Entry point for type-safe table assignment.
 *
 * @tparam Reflect Reflection type containing mapping information.
 * @tparam Model The model type.
 * @tparam Table The table type.
 * @tparam Start Starting index for assignment.
 * @param model The model instance.
 * @param table The table instance.
 * @return A tuple of assigned values.
 */
template <typename Reflect, typename Model, typename Table, size_t Start = 0>
auto assign_table(Model &&model, Table &&table) {
  constexpr auto size = std::tuple_size_v<decltype(Reflect::map_members)>;
  static_assert(Start <= size, "Start index out of range");
  return details::assign_table_impl<Reflect>(
      std::forward<Model>(model), std::forward<Table>(table),
      std::make_index_sequence<size - Start>{});
}

} // namespace details

/**
 * @brief Reflection structure for mapping a model to a table.
 *
 * @tparam Model The model type.
 * @tparam Table The table type.
 */
template <typename Model, typename Table> struct ReflectTable {};

/**
 * @brief Reflection structure for mapping a model to a table row.
 *
 * @tparam Model The model type.
 * @tparam TableRow The table row type.
 */
template <typename Model, typename TableRow> struct ReflectTableRow {};

/**
 * @brief Assigns values from a model to a table using reflection.
 *
 * @tparam Reflect Reflection type containing mapping information.
 * @tparam Model The model type.
 * @tparam Table The table type.
 * @tparam Start Starting index for assignment.
 * @param model The model instance.
 * @param table The table instance.
 * @return A tuple of assigned values.
 */
template <typename Reflect, typename Model, typename Table, size_t Start = 1>
auto assign_table(Model &&model, Table &&table) {
  constexpr auto size = std::tuple_size_v<decltype(Reflect::map_members)>;
  return details::assign_table_impl<Reflect>(
      std::forward<Model>(model), std::forward<Table>(table),
      utils::make_index_sequence_from<Start, size - Start>());
}

/**
 * @brief Generic model class for database operations.
 *
 * @tparam Model The model type.
 * @tparam Table The table type.
 * @tparam Start Starting index for assignment.
 */
template <typename Model, typename Table, size_t Start = 1> class GenericModel {
  using pooled_conn_ptr_type =
      std::shared_ptr<sqlpp::sqlite3::pooled_connection>;
  using Reflect = ReflectTable<Model, Table>;

public:
  /**
   * @brief Inserts a model into the database.
   *
   * @tparam T The model type.
   * @param model The model instance.
   * @return The result of the insert operation.
   */
  template <typename T> static insert_ret_type _insert(T &&model) {
    return utils::DataBaseHelper::execute<insert_ret_type>(
        [](const pooled_conn_ptr_type &conn, T &&model_) {
          static Table table_{};
          // 插入数据
          auto result = (*conn)(
              insert_into(table_).set(assign_table<Reflect, T, Table, Start>(
                  std::forward<T>(model_), std::forward<Table>(table_))));

          // 获取最后插入的自增 ID（关键修改部分）
          in_id_type last_insert_id = result;
          return insert_ret_type{last_insert_id};
        },
        std::forward<T>(model));
  }

  /**
   * @brief Updates a model in the database.
   *
   * @tparam T The model type.
   * @tparam Condition The condition type.
   * @param model The model instance.
   * @param condition The update condition.
   * @return The result of the update operation.
   */
  template <typename T, typename Condition>
  static update_ret_type _update(T &&model, Condition &&condition) {
    return utils::DataBaseHelper::execute<update_ret_type>(
        [](const pooled_conn_ptr_type &conn_, T &&model_,
           Condition &&condition_) {
          static Table table_{};
          (*conn_)(
              sqlpp::update(table_)
                  .set(assign_table<Reflect, T, Table, Start>(
                      std::forward<T>(model_), std::forward<Table>(table_)))
                  .where(std::forward<Condition>(condition_)));
          return true;
        },
        std::forward<T>(model), std::forward<Condition>(condition));
  }

  /**
   * @brief Selects models from the database based on a condition.
   *
   * @tparam Condition The condition type.
   * @param condition The selection condition.
   * @return A container of selected models.
   */
  template <typename Condition>
  static select_ret_type<Model> _select(Condition &&condition) {
    return utils::DataBaseHelper::execute<select_ret_type<Model>>(
        [](const pooled_conn_ptr_type &conn_, Condition &&condition_) {
          static Table table_{};
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

  /**
   * @brief Selects models from the database with pagination.
   *
   * @tparam Condition The condition type.
   * @param condition The selection condition.
   * @param page_size The number of items per page.
   * @param offset The offset for pagination.
   * @return A container of selected models.
   */
  template <typename Condition>
  static select_ret_type<Model>
  _select_from(Condition &&condition, count_type page_size, count_type offset) {
    return utils::DataBaseHelper::execute<select_ret_type<Model>>(
        [limit_ = page_size, offset_ = offset](
            const pooled_conn_ptr_type &conn_, Condition &&condition_) {
          static Table table_{};
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

  /**
   * @brief Removes models from the database based on a condition.
   *
   * @tparam Condition The condition type.
   * @param condition The removal condition.
   * @return The result of the removal operation.
   */
  template <typename Condition>
  static delete_ret_type _remove(Condition &&condition) {
    return utils::DataBaseHelper::execute<delete_ret_type>(
        [](const pooled_conn_ptr_type &conn_, Condition &&condition_) {
          static Table table_{};
          (*conn_)(
              remove_from(table_).where(std::forward<Condition>(condition_)));
          return true;
        },
        std::forward<Condition>(condition));
  }

  /**
   * @brief Counts the number of rows in the table.
   *
   * @return The number of rows in the table.
   */
  static count_type _count() {
    return utils::DataBaseHelper::execute<count_type>(
        [](const pooled_conn_ptr_type &conn_) {
          static Table table_{};
          auto rows = (*conn_)(sqlpp::select(sqlpp::count(table_.id))
                                   .from(table_)
                                   .where(table_.id >= 0));
          return rows.front().count;
        });
  }

  /**
   * @brief Checks if any rows exist in the table based on a condition.
   *
   * @tparam Condition The condition type.
   * @param condition The existence condition.
   * @return True if rows exist, false otherwise.
   */
  template <typename Condition> static bool _exists(Condition &&condition) {
    return !_select(std::forward<Condition>(condition)).empty();
  }
};

} // namespace model

namespace unused {

/**
 * @brief Assigns values from a table to a model using reflection.
 *
 * @tparam Reflect Reflection type containing mapping information.
 * @tparam Model The model type.
 * @tparam Table The table type.
 * @tparam Is Index sequence for tuple iteration.
 * @param table The table instance.
 * @param std::index_sequence<Is...> Index sequence for tuple iteration.
 * @return The assigned model.
 */
template <typename Reflect, typename Model, typename Table, size_t... Is>
Model assign_model_impl(Table &&table, std::index_sequence<Is...>) {
  static Model model;
  ((model.*std::get<Is>(Reflect::map_members).first =
        table.*std::get<Is>(Reflect::map_members).second),
   ...);
  return model;
}

/**
 * @brief Assigns values from a table to a model using reflection.
 *
 * @tparam Reflect Reflection type containing mapping information.
 * @tparam Model The model type.
 * @tparam Table The table type.
 * @tparam Is Index sequence for tuple iteration.
 * @param table The table instance.
 * @param std::index_sequence<Is...> Index sequence for tuple iteration.
 * @return The assigned model.
 */
template <typename Reflect, typename Model, typename Table, size_t... Is>
Model assign_model_impl(const Table &table, std::index_sequence<Is...>) {
  static Model model;
  ((model.*std::get<Is>(Reflect::map_members).first =
        table.*std::get<Is>(Reflect::map_members).second),
   ...);
  return model;
}

/**
 * @brief Assigns values from a table to a model using reflection.
 *
 * @tparam Reflect Reflection type containing mapping information.
 * @tparam Model The model type.
 * @tparam Table The table type.
 * @tparam Start Starting index for assignment.
 * @param table The table instance.
 * @return The assigned model.
 */
template <typename Reflect, typename Model, typename Table, size_t Start = 1>
Model assign_model(Table &&table) {
  constexpr auto size = std::tuple_size_v<decltype(Reflect::map_members)>;
  return assign_model_impl<Reflect, Model, Table, Start>(
      std::forward<Table>(table));
}

} // namespace unused
