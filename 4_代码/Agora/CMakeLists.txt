cmake_minimum_required(VERSION 3.21)

set(CMAKE_SUPPRESS_REGENERATION FALSE)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake; ${CMAKE_MODULE_PATH}")
set(COMPILE_OPTIONS
    -O0 -g -Wall # 打开所有警告
    # -Wextra      # 打开额外的警告 -Werror # 将警告视为错误
    -pedantic # 启用严格的 C++ 标准
)

project(
  Project
  LANGUAGES CXX
  VERSION 1.0)

add_subdirectory(SuperMarketManagementSystem)
