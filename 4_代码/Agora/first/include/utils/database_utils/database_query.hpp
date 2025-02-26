//
// Created by 无铭 on 25-2-23.
//

#ifndef DATABASE_QUERY_HPP
#define DATABASE_QUERY_HPP

#include <utils/database_utils/database_utils.hpp>

namespace utils::database_utils {
/**
*
* @tparam TableRow Table's row type, it's used to assign value to DataType
* @tparam DataType The data type will be returned
*
* @author Ess
*/
template <typename TableRow, typename DataType> struct DataTypeTraits;

/**
* @class GenericDataGetter
* @brief Used to get the database data, the usage is specifying the DataType in
* template,
* @brief then pass a connection_pool pointer, a table variable and a condition
* into method get_data
* @bried then, get_data will return vector<DataType>
* @author Ess
*/
template <typename DataType> struct GenericDataGetter : DataBaseHelper {
    using ReturnType = std::vector<DataType>;

    template <typename Table, typename Condition>
    [[nodiscard]] ReturnType get_data(const conn_pool_ptr_type &conn_pool_ptr,
                                      Table &&table, Condition &&condition) {
        auto query = [](const pooled_conn_ptr_type &conn_, Table &&table_,
                        Condition &&condition_) {
            ReturnType ret{};
            for (const auto &row :
                 (*conn_)(select(all_of(table_))
                              .from(table_)
                              .where(std::forward<Condition>(condition_)))) {
                ret.emplace_back(
                    DataTypeTraits<decltype(row), DataType>::get_args(row));
                              }
            return ret;
        };
        return execute<ReturnType>(conn_pool_ptr->get(), query,
                                   std::forward<Table>(table),
                                   std::forward<Condition>(condition));
    }
};

} // namespace utils
#endif // DATABASE_QUERY_HPP
