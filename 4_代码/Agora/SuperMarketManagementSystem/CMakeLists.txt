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

find_package(fmt REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(Sqlpp11 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Crow REQUIRED)
find_package(Sodium REQUIRED)
find_package(OpenSSL REQUIRED)


message(STATUS "Sqlpp11_DIR: ${Sqlpp11_DIR}")

project(SuperMarketManagementSystem LANGUAGES CXX)

add_executable(${PROJECT_NAME} ${srcs})

target_include_directories(${PROJECT_NAME} PRIVATE ${Sqlpp11_DIR})
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE sqlpp11::sqlpp11 sqlpp11::sqlite3)
target_link_libraries(${PROJECT_NAME} PRIVATE ZLIB::ZLIB)
target_link_libraries(${PROJECT_NAME} PRIVATE Crow::Crow)
target_link_libraries(${PROJECT_NAME} PRIVATE ${sodium_LIBRARY_DEBUG})
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::Crypto OpenSSL::SSL)

if (EnableTest) 
  message(STATUS "Enable unit test configuration")
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1)
  FetchContent_MakeAvailable(googletest)
endif()

# enable_testing()
# file(GLOB UTILS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Utils/*.cpp")
# add_executable(hello_test test/hello_test.cc)
# target_link_libraries(hello_test GTest::gtest_main)
# include(GoogleTest)
# gtest_add_tests(TARGET hello_test)
# gtest_add_tests(TARGET jwt_test)
