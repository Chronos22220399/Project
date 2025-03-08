#pragma once
#include <Utils/DatabaseUtils.hpp>
#include <Utils/Utils.hpp>
#include <sqlpp11/sqlpp11.h>

namespace Model {
namespace details {

template <typename Reflect, typename Model, typename Table, size_t... Is>
auto assign_table_impl(Model &&model, Table &&table,
                       std::index_sequence<Is...>) {
    return std::make_tuple(
        (std::forward<Table>(table).*std::get<Is>(Reflect::map_members).second =
             std::forward<Model>(model).*
             std::get<Is>(Reflect::map_members).first)...);
}
} // namespace details

template <typename Model, typename Table> struct ReflectTable;

template <typename Model, typename TableRow> struct ReflectTableRow {};

template <typename Reflect, typename Model, typename Table, size_t Start = 1>
auto assign_table(Model &&model, Table &&table) {
    constexpr auto size = std::tuple_size_v<decltype(Reflect::map_members)>;
    return details::assign_table_impl<Reflect>(
        std::forward<Model>(model), std::forward<Table>(table),
        Utils::make_index_sequence_from<Start, size - Start>());
}

template <typename Model, typename Table, size_t Start = 1> class GenericModel {
    using pooled_conn_ptr_type =
        std::shared_ptr<sqlpp::sqlite3::pooled_connection>;
    using SelectRetType = std::vector<Model>;
    using InsertRetType = bool;
    using UpdateRetType = bool;
    using DeleteRetType = bool;
    using Reflect = ReflectTable<Model, Table>;

  public:
    template <typename T> InsertRetType insert(T &&model) const {
        return Utils::DataBaseHelper::execute<InsertRetType>(
            [](const pooled_conn_ptr_type &conn, T &&model_) {
                Table table_{};
                (*conn)(insert_into(table_).set(
                    assign_table<Reflect, T, Table, Start>(
                        std::forward<T>(model_), std::forward<Table>(table_))));
                return true;
            },
            std::forward<T>(model));
    }

    template <typename T, typename Condition>
    UpdateRetType update(T &&model, Condition &&condition) const {
        return Utils::DataBaseHelper::execute<UpdateRetType>(
            [](const pooled_conn_ptr_type &conn_, T &&model_,
               Condition &&condition_) {
                Table table_{};
                (*conn_)(sqlpp::update(table_)
                             .set(assign_table<Reflect, T, Table, Start>(
                                 std::forward<T>(model_),
                                 std::forward<Table>(table_)))
                             .where(std::forward<Condition>(condition_)));
                return true;
            },
            std::forward<T>(model), std::forward<Condition>(condition));
    }

    template <typename Condition>
    SelectRetType select(Condition &&condition) const {
        return Utils::DataBaseHelper::execute<SelectRetType>(
            [](const pooled_conn_ptr_type &conn_, Condition &&condition_) {
                Table table_{};
                SelectRetType ret_container{};
                auto select_result =
                    (*conn_)(sqlpp::select(all_of(table_))
                                 .from(table_)
                                 .where(std::forward<Condition>(condition_)));
                for (auto &row : select_result) {
                    ret_container.push_back(
                        ReflectTableRow<Model, decltype(row)>::assign_model(
                            row));
                }
                return ret_container;
            },
            std::forward<Condition>(condition));
    }

    template <typename Condition>
    DeleteRetType remove(Condition &&condition) const {
        return Utils::DataBaseHelper::execute<DeleteRetType>(
            [](const pooled_conn_ptr_type &conn_, Condition &&condition_) {
                Table table_{};
                (*conn_)(remove_from(table_).where(
                    std::forward<Condition>(condition_)));
                return true;
            },
            std::forward<Condition>(condition));
    }
};
} // namespace Model

namespace Unused {
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
} // namespace Unused
