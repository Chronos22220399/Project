file(
  GLOB_RECURSE
  srcs
  CONFIGURE_DEPENDS
  include/*.h
  include/*.hpp
  src/*.c
  src/*.cpp
  src/*.cc)

option(EnableTest "Enable unit tests" OFF)

add_compile_options(-Wno-cpp)

find_package(fmt REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(Sqlpp11 REQUIRED)

set(
  libs 
  fmt::fmt
  sqlpp11::sqlpp11 
  sqlpp11::sqlite3
)

message(STATUS "Sqlpp11_DIR: ${Sqlpp11_DIR}")

project(TestSqlpp11 LANGUAGES CXX)

add_executable(${PROJECT_NAME} ${srcs})

target_include_directories(
  ${PROJECT_NAME} 
  PRIVATE 
  ${Sqlpp11_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE 
  ${libs}
)
