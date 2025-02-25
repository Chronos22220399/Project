//
// Created by 无铭 on 25-2-23.
//

#ifndef DATABASE_UTILS_HPP
#define DATABASE_UTILS_HPP

#include <sqlpp11/sqlite3/connection_config.h>
#include <sqlpp11/sqlite3/connection_pool.h>
#include <sqlpp11/sqlite3/sqlite3.h>
#include <utils/log.hpp>

namespace utils {

/**
 * @brief Provide a unified way to recurd log to facilitate subsequent changes
 * to the log method
 */

/**
 * @param is_debug Indicate whether it's debug mode
 * @param path_to_database Specify the path to database, it must point to a file
 * (when you are using sqlite3)
 * @return unique_ptr<connction_pool> return a unique_ptr which point to a
 * sqlpp::sqlite3::connection_pool
 * @author Ess
 */
[[nodiscard]] inline auto
get_conn_pool_ptr(bool is_debug, const std::string &path_to_database) {
    sqlpp::sqlite3::connection_config config{};
    config.debug = is_debug;
    config.flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
    config.path_to_database = path_to_database;
    auto config_ptr =
        std::make_shared<sqlpp::sqlite3::connection_config>(config);
    auto ptr = std::make_unique<sqlpp::sqlite3::connection_pool>(config_ptr, 8);
    return ptr;
}

/**
 * @class
 * @brief Define the offen used type obout sqlpp connection
 */
struct ConnDefiner {
    using conn_pool_type = sqlpp::sqlite3::connection_pool;
    using conn_pool_ptr_type = std::shared_ptr<conn_pool_type>;
    using pooled_conn_type = sqlpp::sqlite3::pooled_connection;
    using pooled_conn_ptr_type = std::shared_ptr<pooled_conn_type>;
};

/**
 * @class ScopedTranscation
 * @brief Encapsulates database transcations using RAII to prevent data
 * inconsistency
 *
 * The class ensures that a transcation is committed or rolled back
 * automatically when the object go out a Scope,
 *
 * @note The transcation should be commited by hand, if it's not commited and
 * gou out a scope(maybe left the function, or an error ocurred), the
 * destrcuctor will be called and transcation will be rolled back
 * @author Ess
 */
class ScopedTranscation : ConnDefiner {
  public:
    /**
     * @param pc_ptr A pooled_connection wrapped by shared_ptr
     * @note After parameters are initialized, the transcation will be start
     * @author Ess
     */
    explicit ScopedTranscation(pooled_conn_ptr_type pc_ptr)
        : pc_ptr_(std::move(pc_ptr)), is_commited_(false) {
        try {
            if (this->pc_ptr_ == nullptr) {
                throw std::invalid_argument(
                    "invalid pointer to pooled_conn_ptr_type");
            }
            pc_ptr_->start_transaction();
        } catch (const sqlpp::exception &e) {
            LOG("出现数据库错误: {}", e.what());
        } catch (const std::exception &e) {
            LOG("出现系统错误: {}", e.what());
        }
    }

    /**
     * @brief Commit the transcation by hand
     * @author Ess
     */
    void commit() {
        try {
            if (!is_commited_) {
                pc_ptr_->commit_transaction();
                is_commited_ = true;
            }
        } catch (const sqlpp::exception &e) {
            LOG("出现数据库错误: {}", e.what());
        } catch (const std::exception &e) {
            LOG("出现系统错误: {}", e.what());
        }
    }

    /**
     * @brief If transcation isn't committed and the transcation is active, the
     * object will roll back the transcation
     * @author Ess
     */
    ~ScopedTranscation() {
        try {
            if (!is_commited_ || pc_ptr_->is_transaction_active()) {
                pc_ptr_->commit_transaction();
            }
        } catch (const sqlpp::exception &e) {
            LOG("出现系统错误: {}", e.what());
        } catch (const std::exception &e) {
            LOG("出现数据库错误: {}", e.what());
        }
    }

  private:
    pooled_conn_ptr_type pc_ptr_;
    bool is_commited_;
};

/**
 * @class DataBaseHelper
 * @brief Offer user a convenient way to execute his/her database operation to
 * prevents writing duplicate codes
 *
 * execute accept a connection_pool pointer wrapped by shared_ptr, an Operation
 * and it's arguments
 *
 * @author Ess
 */
struct DataBaseHelper : ConnDefiner {
    template <typename RetType, typename Operation, typename... Args>
    static auto execute(const conn_pool_ptr_type &conn_pool_ptr,
                        Operation &&operation, Args &&...args) {
        pooled_conn_ptr_type pooled_conn_ptr =
            std::make_shared<pooled_conn_type>(conn_pool_ptr->get());
        try {
            if (!pooled_conn_ptr->is_connected()) {
                LOG("{}", "数据库未连接");
                return RetType{};
            }
            ScopedTranscation trans{pooled_conn_ptr};
            RetType ret =
                operation(pooled_conn_ptr, std::forward<Args>(args)...);
            trans.commit();
            return ret;
        } catch (const sqlpp::exception &e) {
            LOG("出现数据库错误: {}", e.what());
        } catch (const std::exception &e) {
            LOG("出现系统错误: {}", e.what());
        }
        return RetType{};
    }
};

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
 * @brief Used to get the database data, the usage is specifing the DataType in
 * template,
 * @brief then pass a connection_pool pointer, a table variable and a condition
 * into method get_data
 * @bried then, get_data will return vector<DataType>
 * @author Ess
 */
template <typename DataType> struct GenericDataGetter : utils::DataBaseHelper {
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
        return execute<ReturnType>(conn_pool_ptr, query,
                                   std::forward<Table>(table),
                                   std::forward<Condition>(condition));
    }
};

} // namespace utils
#endif // DATABASE_UTILS_HPP
