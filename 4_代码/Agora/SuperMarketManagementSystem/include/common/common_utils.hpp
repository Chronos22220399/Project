#pragma once

#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <chrono>
#include <common/uni_define.h>
#include <crow.h>
#include <filesystem>
#include <functional>
#include <future>
#include <model/db/goods/goods_price.h>
#include <nlohmann/json.hpp>
#include <optional>
#include <sqlpp11/data_types.h>
#include <sqlpp11/sqlpp11.h>
#include <vector>

/**
 * @file utils.hpp
 * @author Ess
 * @brief 通用模板工具与函数，包括索引序列生成、并发循环执行、项目路径处理等
 * @version 1.0
 * @date 2025-04-20
 */

namespace details {

/**
 * @brief 递归生成偶数或奇数的索引序列（从 N 开始递减，每次减 2）。
 *
 * @tparam N 起始索引值（必须为偶数或奇数）。
 * @tparam Is 累积展开的索引序列参数包。
 *
 * @note 当 N 为 0 或 1 时终止递归展开，生成最终的 std::index_sequence。
 */
template <std::size_t N, std::size_t... Is>
struct make_even_or_odd_sequence
    : make_even_or_odd_sequence<N - 2, N - 2, Is...> {};

/**
 * @brief 停止条件（N 为 0），用于生成 std::index_sequence。
 *
 * @tparam Is 展开的索引值。
 */
template <std::size_t... Is> struct make_even_or_odd_sequence<0, Is...> {
  using type = std::index_sequence<Is...>;
};

/**
 * @brief 停止条件（N 为 1），用于生成 std::index_sequence。
 *
 * @tparam Is 展开的索引值。
 */
template <std::size_t... Is> struct make_even_or_odd_sequence<1, Is...> {
  using type = std::index_sequence<Is...>;
};

/**
 * @brief 为给定的 index_sequence 中每个索引值加上 N，生成新的 index_sequence。
 *
 * @tparam N 偏移量，将用于加到每个索引上。
 * @tparam Is 原始 index_sequence 中的索引值。
 *
 * @return std::index_sequence<N + Is...> 新的索引序列。
 */
template <std::size_t N, std::size_t... Is>
auto make_index_sequence_from(std::index_sequence<Is...>) {
  return std::index_sequence<N + Is...>{};
}

} // namespace details

namespace utils {

/**
 * @brief 递归查找指定根目录名称对应的路径，返回项目根路径。
 *
 * @param path 当前路径。
 * @param root_dir_name 根目录名（如项目根文件夹名）。
 * @return std::filesystem::path 项目根路径。
 */
inline std::filesystem::path get_project_root_path(std::filesystem::path path,
                                                   std::string root_dir_name) {
  std::string current_path = std::string(path.c_str());
  bool in_root_dir =
      (current_path.rfind(root_dir_name) + root_dir_name.length() ==
       current_path.length());
  if (!in_root_dir) {
    return get_project_root_path(path.parent_path(), root_dir_name);
  } else {
    return path;
  }
}

/**
 * @brief 并发执行函数 LoopNum 次，函数不带索引参数。
 *
 * @tparam LoopNum 执行次数。
 */
template <size_t LoopNum> struct ForLoop {
  /**
   * @brief 运行传入函数 LoopNum 次，每次并发执行。
   *
   * @tparam Function 可调用对象类型。
   * @tparam Args 参数类型。
   * @param func 需要并发执行的函数。
   * @param args 传递给函数的参数。
   */
  template <typename Function, typename... Args>
  static auto run(Function &&func, Args &&...args) {
    std::vector<std::future<void>> futures;
    futures.reserve(LoopNum);
    for (auto i = 0; i < LoopNum; ++i) {
      futures.emplace_back(std::async(std::launch::async, [&func, &args...] {
        std::invoke(std::forward<Function>(func), std::forward<Args>(args)...);
      }));
    }
    for (auto &future : futures) {
      future.wait();
    }
  }
};

/**
 * @brief 生成长度为 N 的偶数或奇数索引序列。
 *
 * @tparam N 目标索引长度。
 */
template <size_t N>
using make_even_index_sequence =
    typename details::make_even_or_odd_sequence<N + 2>::type;

/**
 * @brief 生成一个从 N 开始，长度为 L 的索引序列。
 *
 * @tparam N 起始索引值。
 * @tparam L 索引数量。
 *
 * @return std::index_sequence<N, N+1, ..., N+L-1>
 */
template <size_t N, size_t L> auto make_index_sequence_from() {
  return details::make_index_sequence_from<N>(std::make_index_sequence<L>{});
}

/**
 * @brief 生成一个伪造的全局唯一 ID（用于测试或占位）。
 *
 * @return std::string 固定字符串 "1"（测试阶段固定）。
 */
inline std::string create_id(const std::string &prefix) {
  boost::uuids::uuid uuid = boost::uuids::random_generator()();
  return prefix + boost::uuids::to_string(uuid);
}

inline std::optional<nlohmann::json> try_parse_json(const std::string &body) {
  try {
    return nlohmann::json::parse(body);
  } catch (...) {
    return std::nullopt;
  }
}

// 字符串转时间点
inline datetime_type string_to_time(const std::string &str) {
  std::tm tm = {};
  int microseconds = 0;
  std::istringstream iss(str);

  // 解析基础时间
  iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

  // 处理微秒部分
  char dot;
  if (iss >> dot && dot == '.' && iss >> microseconds) {
    microseconds = std::min(microseconds, 999999);
  }

  // 构造时间点
  auto sys_time = std::chrono::system_clock::from_time_t(std::mktime(&tm)) +
                  std::chrono::microseconds(microseconds);

  return datetime_type(
      std::chrono::time_point_cast<datetime_type::duration>(sys_time));
}

// 时间点转字符串
inline std::string time_to_string(const datetime_type &tp) {
  const auto sys_time = std::chrono::system_clock::to_time_t(
      std::chrono::time_point_cast<std::chrono::system_clock::duration>(tp));

  std::ostringstream oss;
  oss << std::put_time(std::localtime(&sys_time), "%Y-%m-%d %H:%M:%S");

  // 添加微秒
  const auto us = std::chrono::duration_cast<std::chrono::microseconds>(
                      tp.time_since_epoch())
                      .count() %
                  1000000;

  if (us > 0) {
    oss << "." << std::setw(6) << std::setfill('0') << us;
  }

  return oss.str();
}

template <typename T> inline auto to_sqlpp_value(T &&value) {
  return sqlpp::value(std::forward<T>(value));
}
// 文本处理特化
template <> inline auto to_sqlpp_value<std::string>(std::string &&value) {
  return sqlpp::value(value); // 使用value而不是text
}

template <typename Elem, typename Container>
bool in(const Elem &elem, const Container &container) {
  for (auto &e : container) {
    if (e == elem) {
      return true;
    }
  }
  return false;
}

} // namespace utils
