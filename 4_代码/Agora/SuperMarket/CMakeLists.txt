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

find_package(fmt REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(Sqlpp11)
find_package(Crow REQUIRED)

message(STATUS "Sqlpp11_DIR: ${Sqlpp11_DIR}")

project(SuperMarket LANGUAGES CXX)

add_executable(${PROJECT_NAME} ${srcs})

target_include_directories(${PROJECT_NAME} PRIVATE ${Sqlpp11_DIR})
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_LIST_DIR}/datas/)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE sqlpp11::sqlpp11 sqlpp11::sqlite3)
target_link_libraries(${PROJECT_NAME} PRIVATE Crow::Crow)
