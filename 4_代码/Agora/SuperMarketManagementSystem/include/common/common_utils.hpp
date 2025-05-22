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
auto make_index_sequence_from(std::index_sequence<Is...>)
{
  return std::index_sequence<N + Is...>{};
}

}  // namespace details

namespace utils {

/**
 * @brief 递归查找指定根目录名称对应的路径，返回项目根路径。
 *
 * @param path 当前路径。
 * @param root_dir_name 根目录名（如项目根文件夹名）。
 * @return std::filesystem::path 项目根路径。
 */
inline std::filesystem::path get_project_root_path(std::filesystem::path path,
                                                   std::string root_dir_name)
{
  std::string current_path = std::string(path.c_str());
  bool in_root_dir = (current_path.rfind(root_dir_name) + root_dir_name.length()
                      == current_path.length());
  if (!in_root_dir) {
    return get_project_root_path(path.parent_path(), root_dir_name);
  }
  else {
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
  static auto run(Function&& func, Args&&... args)
  {
    std::vector<std::future<void>> futures;
    futures.reserve(LoopNum);
    for (auto i = 0; i < LoopNum; ++i) {
      futures.emplace_back(std::async(std::launch::async, [ &func, &args... ] {
        std::invoke(std::forward<Function>(func), std::forward<Args>(args)...);
      }));
    }
    for (auto& future : futures) {
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
template <size_t N, size_t L> auto make_index_sequence_from()
{
  // 调用 details 命名空间中的辅助函数生成索引序列
  return details::make_index_sequence_from<N>(std::make_index_sequence<L>{});
}

/**
 * @brief 生成一个伪造的全局唯一 ID（用于测试或占位）。
 *
 * @return std::string 有 boost::uuid 得到的 uuid（测试阶段固定）。
 */
inline std::string create_id(const std::string& prefix)
{
  // 使用 Boost 库生成随机 UUID
  boost::uuids::uuid uuid = boost::uuids::random_generator()();
  // 将 UUID 转换为字符串并添加前缀
  return prefix + boost::uuids::to_string(uuid);
}

/**
 * @brief 尝试解析 JSON 字符串。
 *
 * @param body JSON 格式的字符串。
 * @return std::optional<nlohmann::json> 如果解析成功，返回 JSON 对象；否则返回
 * std::nullopt。
 */
inline std::optional<nlohmann::json> try_parse_json(const std::string& body)
{
  try {
    // 使用 nlohmann::json 解析字符串
    return nlohmann::json::parse(body);
  }
  catch (...) {
    // 捕获所有异常并返回空值
    LOG("parse json failed");
    return std::nullopt;
  }
}

/**
 * @brief 将字符串转换为时间点。
 *
 * @param str 时间字符串，格式为 "YYYY-MM-DD HH:MM:SS.ffffff"。
 * @return datetime_type 转换后的时间点。
 * @throws std::invalid_argument 如果时间字符串格式非法。
 */
inline datetime_type string_to_time(const std::string& str)
{
  std::tm tm = {};
  int microseconds = 0;
  std::istringstream iss(str);

  // 解析基础时间
  iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
  if (iss.fail()) {
    throw std::invalid_argument("Invalid time format: " + str);
  }

  // 处理微秒部分
  char dot;
  if (iss >> dot && dot == '.' && iss >> microseconds) {
    // 限制微秒值的最大值为 999999
    microseconds = std::min(microseconds, 999999);
  }

  // 构造时间点
  auto sys_time = std::chrono::system_clock::from_time_t(std::mktime(&tm))
                  + std::chrono::microseconds(microseconds);

  // 转换为自定义的 datetime_type 类型
  return datetime_type(
    std::chrono::time_point_cast<datetime_type::duration>(sys_time));
}

/**
 * @brief 将时间点转换为字符串。
 *
 * @param tp 时间点。
 * @return std::string 转换后的时间字符串，格式为 "YYYY-MM-DD HH:MM:SS.ffffff"。
 */
inline std::string time_to_string(const datetime_type& tp)
{
  const auto sys_time = std::chrono::system_clock::to_time_t(
    std::chrono::time_point_cast<std::chrono::system_clock::duration>(tp));

  std::ostringstream oss;
  // 格式化基础时间部分
  oss << std::put_time(std::localtime(&sys_time), "%Y-%m-%d %H:%M:%S");

  // 添加微秒部分
  const auto us =
    std::chrono::duration_cast<std::chrono::microseconds>(tp.time_since_epoch())
      .count()
    % 1000000;

  if (us > 0) {
    // 格式化微秒部分为 6 位数字
    oss << "." << std::setw(6) << std::setfill('0') << us;
  }

  return oss.str();
}

/**
 * @brief 将任意类型的值转换为 SQL++ 支持的值。
 *
 * @tparam T 值的类型。
 * @param value 要转换的值。
 * @return 转换后的 SQL++ 值。
 */
template <typename T> inline auto to_sqlpp_value(T&& value)
{
  // 使用 sqlpp::value 包装值
  return sqlpp::value(std::forward<T>(value));
}

/**
 * @brief 将字符串类型的值转换为 SQL++ 支持的值（特化版本）。
 *
 * @param value 要转换的字符串值。
 * @return 转换后的 SQL++ 值。
 */
template <> inline auto to_sqlpp_value<std::string>(std::string&& value)
{
  // 使用 sqlpp::value 包装字符串值
  return sqlpp::value(value);  // 使用 value 而不是 text
}

/**
 * @brief 检查元素是否存在于容器中。
 *
 * @tparam Elem 元素类型。
 * @tparam Container 容器类型。
 * @param elem 要检查的元素。
 * @param container 容器。
 * @return true 如果元素存在于容器中。
 * @return false 如果元素不存在于容器中。
 */
template <typename Elem, typename Container>
bool in(const Elem& elem, const Container& container)
{
  // 遍历容器中的每个元素
  for (auto& e : container) {
    if (e == elem) {
      // 如果找到匹配的元素，返回 true
      return true;
    }
  }
  // 如果未找到匹配的元素，返回 false
  return false;
}

inline std::string get_current_iso8601()
{
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);

  std::tm tm_buf;
  gmtime_r(&in_time_t, &tm_buf);

  std::stringstream ss;
  ss << std::put_time(&tm_buf, "%Y-%m-%dT%H:%M:%SZ");
  return ss.str();
}

template <typename Func, typename ErrHandler =
                           std::function<crow::response(const std::exception&)>>
auto safeJsonExecution(
  const std::string& body, Func&& servFunc,
  ErrHandler&& errFunc = [](const std::exception& e) {
    return SET_ERR_RESPONSE(500, "Unknown error");
  }) -> std::invoke_result_t<Func, const nlohmann::json&>
{

  nlohmann::json j;
  CHECK_AND_GET_JSON(j);

  try {
    return std::forward<Func>(servFunc)(j);
  }
  catch (const std::exception& e) {
    if constexpr (std::is_same_v<void, std::invoke_result_t<
                                         ErrHandler, const std::exception&>>) {
      return SET_ERR_RESPONSE(500, e.what());
    }
    return std::forward<ErrHandler>(errFunc)(e);
  }
}

inline crow::response to_response(const ServiceResult& res,
                                  int success_code = 200)
{
  if (!res.success) {
    return crow::response(
      500, nlohmann::json{{"code", 500}, {"error", res.error}}.dump());
  }
  return crow::response(
    success_code,
    nlohmann::json{{"code", success_code}, {"data", res.data}}.dump());
}
}  // namespace utils
