//
// Created by 无铭 on 25-2-26.
//

#ifndef DATABASE_UTILS_HPP
#define DATABASE_UTILS_HPP

#include <sqlpp11/sqlite3/connection_config.h>
#include <sqlpp11/sqlite3/connection_pool.h>
#include <sqlpp11/sqlite3/sqlite3.h>
#include <utils/utils.hpp>
#include <utils/log.hpp>

namespace utils::database_utils {

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
* @return unique_ptr<connction_pool> return a unique_ptr which point to a
* sqlpp::sqlite3::connection_pool
* @author Ess
*/
[[nodiscard]] static auto
get_conn_pool_ptr() {
    static sqlpp::sqlite3::connection_config config{};
    static std::once_flag flag;
    std::call_once(flag, [&]() {
        static auto root_dir_path = utils::get_project_root_path(std::filesystem::current_path(), "Agora");
        config.debug = true;
        config.flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
        config.path_to_database = "/first/datas/sqlite3/admin.sqlite3";
        fmt::println("Current Path: {}", root_dir_path.c_str());
    });
    static auto config_ptr =
            std::make_shared<sqlpp::sqlite3::connection_config>(config);
    static auto conn_pool = std::make_shared<ConnDefiner::conn_pool_type>(config_ptr, 8);
    return conn_pool;
}


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
    static auto execute(pooled_conn_ptr_type pooled_conn_ptr, Operation &&operation, Args &&...args) {
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

    class
}
#endif //DATABASE_UTILS_HPP
