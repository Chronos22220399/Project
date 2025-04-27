#pragma once

#include <cstdint>
#include <sqlpp11/data_types.h>
#include <vector>

/**
 * @file types.hpp
 * @author Ess
 * @brief 定义通用类型别名、日志宏、JSON检查宏，统一常用基础功能
 * @version 1.0
 * @date 2025-04-20
 */

/// @brief 唯一标识符类型（通常用于数据库中的主键 ID）
using id_type = long int;

/// @brief 日期计数类型（用于表示天数等时间间隔）
using date_cnt_type = long int;

/// @brief 64位无符号整型（用于计数场景，如记录条数）
using count_type = std::uint64_t;

/// @brief 时间点类型（微秒精度）
using datetime_type = sqlpp::chrono::microsecond_point;

/// @brief 查询返回的统一模板类型（返回若干 Model 实例）
template <typename Model> using select_ret_type = std::vector<Model>;

/// @brief 插入操作返回类型（表示是否成功）
using insert_ret_type = bool;

/// @brief 更新操作返回类型（表示是否成功）
using update_ret_type = bool;

/// @brief 删除操作返回类型（表示是否成功）
using delete_ret_type = bool;

/**
 * @brief 打印带有文件名、函数名和行号的格式化日志信息。
 *
 * @note 使用示例：`LOG("Current value: {}", value);`
 */
#define LOG(...)                                                               \
  fmt::println("[{}:{}:{}]: {}", __FILE_NAME__, __FUNCTION__, __LINE__,        \
               fmt::format(__VA_ARGS__))

/**
 * @brief 生成带有文件名、函数名和行号的格式化字符串。
 *
 * @note 使用示例：`auto log_str = FORMAT_LOG_STR("Value is {}", value);`
 */
#define FORMAT_LOG_STR(...)                                                    \
  fmt::format("[{}:{}:{}]: {}", __FILE_NAME__, __FUNCTION__, __LINE__,         \
              __VA_ARGS__)

/**
 * @brief 尝试解析 body 中的 JSON，如果解析失败则返回 400 错误。
 *
 * @param j JSON 对象（由宏内部赋值）
 *
 * @note 使用示例：
 * @code
 * nlohmann::json j;
 * CHECK_AND_GET_JSON(j);
 * @endcode
 */
#define CHECK_AND_GET_JSON(j)                                                  \
  auto j_opt = utils::try_parse_json(body);                                    \
  if (!j_opt)                                                                  \
    return crow::response(400, "Invalid JSON");                                \
  j = std::move(j_opt.value());

/**
 * @brief 检查 JSON 中是否包含指定字段，不存在则返回 400 错误。
 *
 * @param j JSON 对象
 * @param field 要检查的字段名
 *
 * @note 使用示例：
 * @code
 * CHECK_REQUIRED_FIELD(j, "name");
 * @endcode
 */
#define CHECK_REQUIRED_FIELD(j, field)                                         \
  if (!(j).contains((field)))                                                  \
  return crow::response(400, fmt::format("Missing field: {}.", (field)))

/**
 * @brief 批量检查 JSON 中是否包含所有指定字段，不存在则返回 400 错误。
 *
 * @param j JSON 对象
 * @param container 存放所有字段名的容器（如 std::vector<std::string>）
 *
 * @note 使用示例：
 * @code
 * const std::vector<std::string> required = {"id", "name"};
 * CHECK_REQUIRED_FIELDS(j, required);
 * @endcode
 */
#define CHECK_REQUIRED_FIELDS(j, container)                                    \
  for (const auto &field : (container)) {                                      \
    if (!(j).contains(field)) {                                                \
      return crow::response(400, fmt::format("Missing field: {}.", field));    \
    }                                                                          \
  }
