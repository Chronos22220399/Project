//
// Created by 无铭 on 25-2-23.
//

#ifndef LOG_HPP
#define LOG_HPP
#include <fmt/format.h>

/**
* @brief Provide a unified way to recurd log to facilitate subsequent changes
* to the log method
*/
#define LOG(...)                                                               \
  fmt::println("[{}:{}:{}]: {}", __FILE_NAME__, __FUNCTION__, __LINE__,        \
               fmt::format(__VA_ARGS__))

#define FORMAT_LOG_STR(...)                                                    \
  fmt::format("[{}:{}:{}]: {}", __FILE_NAME__, __FUNCTION__, __LINE__,         \
              __VA_ARGS__)

#endif //LOG_HPP
