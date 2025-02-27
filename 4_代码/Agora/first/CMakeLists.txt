file(
  GLOB_RECURSE
  srcs
  CONFIGURE_DEPENDES
  include/*.h
  include/*.hpp
  datas/include/*.h
  src/*.c
  src/*.cpp
  src/*.cc)

# set(CMAKE_PREFIX_PATH "$ENV{HOME}/.install; ${CMAKE_PREFIX_PATH}")

find_package(fmt REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(Sqlpp11)
find_package(Crow REQUIRED)

message(STATUS "Sqlpp11_DIR: ${Sqlpp11_DIR}")

project(first LANGUAGES CXX)

add_executable(
  ${PROJECT_NAME}
  ${srcs}
  include/utils/utils.hpp
  include/utils/log.hpp
  include/utils/database_utils/database_query.hpp
  include/Models/AdminModel.h
  src/Models/AdminModel.cpp
  include/utils/database_utils/database_utils.hpp
  include/cases/get_pooled_conn_ptr_case.hpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${Sqlpp11_DIR})
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_LIST_DIR}/datas/)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE sqlpp11::sqlpp11 sqlpp11::sqlite3)
target_link_libraries(${PROJECT_NAME} PRIVATE Crow::Crow)
