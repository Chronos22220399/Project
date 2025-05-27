#pragma once
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sqlpp11/chrono.h>

using datetime_type = sqlpp::chrono::microsecond_point;

using date_type = sqlpp::chrono::day_point;

using time_type = std::chrono::microseconds;

/**
 * @brief 将字符串转换为时间点。
 *
 * @param str 时间字符串，格式为 "YYYY-MM-DD HH:MM:SS.ffffff"。
 * @return datetime_type 转换后的时间点。
 * @throws std::invalid_argument 如果时间字符串格式非法。
 */
inline datetime_type string_to_datetime(const std::string& str)
{
  std::tm tm = {};
  int microseconds = 0;
  std::istringstream iss(str);

  // 解析基础时间
  iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
  if (iss.fail()) {
    throw std::invalid_argument("Invalid datetime format: " + str);
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
inline std::string datetime_to_string(const datetime_type& tp)

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
 * @brief 将字符串转换为日期。
 *
 * @param str 日期字符串，格式为 "YYYY-MM-DD"。
 * @return date_type 转换后的日期时间点（时间部分为 00:00:00）。
 * @throws std::invalid_argument 如果日期字符串格式非法。
 */
inline date_type string_to_date(const std::string& str)
{
  std::tm tm = {};
  std::istringstream iss(str);
  iss >> std::get_time(&tm, "%Y-%m-%d");
  if (iss.fail()) {
    throw std::invalid_argument("Invalid date format: " + str);
  }

  auto sys_time = std::chrono::system_clock::from_time_t(std::mktime(&tm));
  return date_type(std::chrono::time_point_cast<date_type::duration>(sys_time));
}


/**
 * @brief 将日期时间点转换为字符串。
 *
 * @param tp 日期时间点（忽略时间部分）。
 * @return std::string 转换后的字符串，格式为 "YYYY-MM-DD"。
 */
inline std::string date_to_string(const date_type& tp)
{
  const auto sys_time = std::chrono::system_clock::to_time_t(
    std::chrono::time_point_cast<std::chrono::system_clock::duration>(tp));

  std::ostringstream oss;
  oss << std::put_time(std::localtime(&sys_time), "%Y-%m-%d");
  return oss.str();
}


/**
 * @brief 将字符串转换为时间（微秒精度）。
 * @param str 格式 "HH:MM:SS.ffffff"
 * @return time_type
 * @throws std::invalid_argument
 */
inline time_type string_to_time(const std::string& str)
{
  int hour = 0, min = 0, sec = 0;
  char sep1, sep2;
  size_t dot_pos = str.find('.');
  std::string time_part = str.substr(0, dot_pos);
  std::istringstream iss(time_part);
  iss >> hour >> sep1 >> min >> sep2 >> sec;
  if (iss.fail() || sep1 != ':' || sep2 != ':')
    throw std::invalid_argument("Invalid time format: " + str);
  // 校验范围
  if (hour < 0 || hour > 23 || min < 0 || min > 59 || sec < 0 || sec > 59)
    throw std::invalid_argument("Time out of range: " + str);

  int microseconds_ = 0;
  if (dot_pos != std::string::npos) {
    std::string micro_str = str.substr(dot_pos + 1);
    if (micro_str.length() > 6)
      micro_str = micro_str.substr(0, 6);
    while (micro_str.length() < 6)
      micro_str += '0';  // 补足6位
    if (!micro_str.empty())
      microseconds_ = std::stoi(micro_str);
  }
  using namespace std::chrono;
  auto us =
    hours(hour) + minutes(min) + seconds(sec) + microseconds(microseconds_);
  return time_type(us);
}

/**
 * @brief 将时间类型（微秒）转换为字符串。
 * @param tp
 * @return "HH:MM:SS.ffffff"
 */
inline std::string time_to_string(const time_type& tp)
{
  using namespace std::chrono;
  int64_t us = tp.count();
  int hour = static_cast<int>(us / (1000ll * 1000 * 60 * 60));
  us %= (1000ll * 1000 * 60 * 60);
  int min = static_cast<int>(us / (1000 * 1000 * 60));
  us %= (1000ll * 1000 * 60);
  int sec = static_cast<int>(us / (1000ll * 1000));
  int micro = static_cast<int>(us % (1000ll * 1000));
  std::ostringstream oss;
  oss << std::setw(2) << std::setfill('0') << hour << ":" << std::setw(2)
      << std::setfill('0') << min << ":" << std::setw(2) << std::setfill('0')
      << sec << "." << std::setw(6) << std::setfill('0') << micro;
  return oss.str();
}
