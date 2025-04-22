#include <common/common_utils.hpp>
#include <common/config_utils.h>
#include <common/uni_define.h>
#include <fmt/format.h>
#include <sqlpp11/sqlite3/connection_config.h>
#include <sqlpp11/sqlite3/connection_pool.h>
#include <sqlpp11/sqlite3/sqlite3.h>

namespace utils {
using conn_pool_type = sqlpp::sqlite3::connection_pool;
using conn_pool_ptr_type = std::shared_ptr<conn_pool_type>;
using pooled_conn_type = sqlpp::sqlite3::pooled_connection;
using pooled_conn_ptr_type = std::shared_ptr<pooled_conn_type>;

inline auto config_file = "./SuperMarketManagementSystem/config/config.json";
inline utils::ConfigManager configManager(config_file);

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
    config.path_to_database = std::string(root_dir_path) + databasePath;
  });
  static auto config_ptr =
      std::make_shared<sqlpp::sqlite3::connection_config>(config);
  static auto conn_pool = conn_pool_type(config_ptr, 8);
  return std::make_unique<pooled_conn_type>(conn_pool.get());
}

class ScopedTranscation {
public:
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
struct DataBaseHelper {
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
