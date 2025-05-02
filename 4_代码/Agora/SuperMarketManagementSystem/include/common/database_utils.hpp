/**
 * @file
 * @brief This file contains utility classes and functions for managing SQLite
 * database connections and transactions.
 *
 * It includes a connection pool, scoped transaction management, and a helper
 * class for executing database operations.
 *
 * @author Ess
 */

#pragma once
#include <common/common_utils.hpp>
#include <common/config_utils.h>
#include <common/uni_define.h>
#include <fmt/format.h>
#include <sqlpp11/sqlite3/connection_config.h>
#include <sqlpp11/sqlite3/connection_pool.h>
#include <sqlpp11/sqlite3/sqlite3.h>

namespace utils {

/**
 * @typedef conn_pool_type
 * @brief Alias for the SQLite connection pool type.
 */
using conn_pool_type = sqlpp::sqlite3::connection_pool;

/**
 * @typedef conn_pool_ptr_type
 * @brief Alias for a shared pointer to the SQLite connection pool.
 */
using conn_pool_ptr_type = std::shared_ptr<conn_pool_type>;

/**
 * @typedef pooled_conn_type
 * @brief Alias for a pooled SQLite connection type.
 */
using pooled_conn_type = sqlpp::sqlite3::pooled_connection;

/**
 * @typedef pooled_conn_ptr_type
 * @brief Alias for a shared pointer to a pooled SQLite connection.
 */
using pooled_conn_ptr_type = std::shared_ptr<pooled_conn_type>;

/**
 * @var config_file
 * @brief Path to the configuration file.
 */
inline auto config_file = "./SuperMarketManagementSystem/config/config.json";

/**
 * @var configManager
 * @brief Instance of ConfigManager initialized with the configuration file.
 */
inline utils::ConfigManager configManager(config_file);

/**
 * @brief Retrieves a unique pointer to a pooled SQLite connection.
 *
 * This function initializes the SQLite connection configuration and connection
 * pool on the first call and returns a unique pointer to a pooled connection.
 *
 * @return std::unique_ptr<pooled_conn_type> Unique pointer to a pooled SQLite
 * connection.
 */
[[nodiscard]] static auto get_pooled_conn_ptr() {
  static sqlpp::sqlite3::connection_config config{};
  static std::once_flag flag;
  std::call_once(flag, [&]() {
    static auto root_dir_path =
        utils::get_project_root_path(std::filesystem::current_path(), "Agora");
    fmt::println("Current Path: {}", root_dir_path.c_str());
    config.debug = true;
    config.flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
    auto databasePath = configManager.getDatabasePath();
    // config.path_to_database = std::string(root_dir_path) + databasePath;
    config.path_to_database = databasePath;
  });
  static auto config_ptr =
      std::make_shared<sqlpp::sqlite3::connection_config>(config);
  static auto conn_pool = conn_pool_type(config_ptr, 8);
  return std::make_unique<pooled_conn_type>(conn_pool.get());
}

/**
 * @class ScopedTranscation
 * @brief Manages a database transaction within a scope.
 *
 * This class ensures that a transaction is started upon construction and
 * committed upon destruction, unless explicitly committed earlier.
 */
class ScopedTranscation {
public:
  /**
   * @brief Constructs a ScopedTranscation and starts a transaction.
   *
   * @param pc_ptr Shared pointer to a pooled SQLite connection.
   * @throw std::invalid_argument If the provided connection pointer is null.
   */
  explicit ScopedTranscation(pooled_conn_ptr_type pc_ptr)
      : pc_ptr_(std::move(pc_ptr)), is_commited_(false) {
    try {
      if (this->pc_ptr_ == nullptr) {
        throw std::invalid_argument("invalid pointer to pooled_conn_ptr_type");
      }
      pc_ptr_->start_transaction();
    } catch (const sqlpp::exception &e) {
      LOG("出现数据库错误: {}", e.what());
    } catch (const std::exception &e) {
      LOG("出现系统错误: {}", e.what());
    }
  }

  /**
   * @brief Commits the transaction if it has not been committed yet.
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
   * @brief Destructor that commits the transaction if it is still active.
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
  pooled_conn_ptr_type
      pc_ptr_;       ///< Shared pointer to a pooled SQLite connection.
  bool is_commited_; ///< Indicates whether the transaction has been committed.
};

/**
 * @struct DataBaseHelper
 * @brief Provides a convenient way to execute database operations.
 *
 * This helper struct prevents code duplication by wrapping database operations
 * in a reusable execute method.
 */
struct DataBaseHelper {
  /**
   * @brief Executes a database operation with the provided arguments.
   *
   * @tparam RetType The return type of the operation.
   * @tparam Operation The type of the operation to execute.
   * @tparam Args The types of the arguments to pass to the operation.
   * @param operation The operation to execute.
   * @param args The arguments to pass to the operation.
   * @return RetType The result of the operation.
   */
  template <typename RetType, typename Operation, typename... Args>
  static auto execute(Operation &&operation, Args &&...args) {
    try {
      pooled_conn_ptr_type pooled_conn_ptr = get_pooled_conn_ptr();
      if (!pooled_conn_ptr->is_connected()) {
        LOG("{}", "数据库未连接");
        return RetType{};
      }
      ScopedTranscation trans{pooled_conn_ptr};
      RetType ret = operation(pooled_conn_ptr, std::forward<Args>(args)...);
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

} // namespace utils
