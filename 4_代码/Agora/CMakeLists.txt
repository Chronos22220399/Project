cmake_minimum_required(VERSION 3.15)

# 强制覆盖子项目的旧版策略设置
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)  # 处理googletest的版本警告

# 全局编译设置
set(CMAKE_SUPPRESS_REGENERATION FALSE)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 优先查找现代CONFIG模式包
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake; ${CMAKE_MODULE_PATH}")
set(COMPILE_OPTIONS
    -O0 -g -Wall # 打开所有警告
    # -Wextra      # 打开额外的警告 -Werror # 将警告视为错误
    -pedantic # 启用严格的 C++ 标准
    -Wno-cpp
)

project(
  Project
  LANGUAGES CXX
  VERSION 1.0)

# add_subdirectory(SuperMarketManagementSystem)
add_subdirectory(TestSqlpp11)
