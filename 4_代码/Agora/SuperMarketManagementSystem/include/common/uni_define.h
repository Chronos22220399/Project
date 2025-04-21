#pragma once

#include <cstdint>
#include <vector>

/**
 * @file types.hpp
 * @author Ess
 * @brief 定义通用 ID 类型、日期计数类型以及日志宏
 * @version 1.0
 * @date 2025-04-20
 */

/**
 * @brief 唯一标识符类型，用于数据库 ID 等。
 */
using id_type = long int;

/**
 * @brief 日期计数类型，通常用于表示有效期（如天数等）。
 */
using date_cnt_type = long int;

/**
 * @brief 记录带文件名、函数名和行号的格式化日志信息。
 *
 * @note 使用方式：`LOG("message: {}", value);`
 */
#define LOG(...)                                                               \
  fmt::println("[{}:{}:{}]: {}", __FILE_NAME__, __FUNCTION__, __LINE__,        \
               fmt::format(__VA_ARGS__))

/**
 * @brief 生成带调试信息（文件名、函数名、行号）的格式化字符串。
 *
 * @note 使用方式：`auto log_str = FORMAT_LOG_STR("value is {}", value);`
 */
#define FORMAT_LOG_STR(...)                                                    \
  fmt::format("[{}:{}:{}]: {}", __FILE_NAME__, __FUNCTION__, __LINE__,         \
              __VA_ARGS__)

template <typename Model> using select_ret_type = std::vector<Model>;
using insert_ret_type = bool;
using update_ret_type = bool;
using delete_ret_type = bool;
using count_type = std::uint64_t;
