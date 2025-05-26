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

set(EnableTest ON)

add_compile_options(-Wno-cpp)

find_package(fmt REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(Sqlpp11 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Crow REQUIRED)
find_package(Sodium REQUIRED)
find_package(OpenSSL REQUIRED)

set(
  libs 
  fmt::fmt
  sqlpp11::sqlpp11 
  sqlpp11::sqlite3
  ZLIB::ZLIB 
  Crow::Crow
  ${sodium_LIBRARY_DEBUG}
  ${OPENSSL_SSL_LIBRARY}
  ${OPENSSL_CRYPTO_LIBRARY}
)

message(STATUS "Sqlpp11_DIR: ${Sqlpp11_DIR}")

project(SuperMarketManagementSystem LANGUAGES CXX)

add_executable(${PROJECT_NAME} ${srcs})

target_include_directories(
  ${PROJECT_NAME} 
  PRIVATE 
  ${Sqlpp11_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/include
  # ${CMAKE_CURRENT_LIST_DIR}/third_party/jwt-cpp/include
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE 
  ${libs}
)

if (EnableTest) 
  message(STATUS "Enable unit test configuration")
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1)
  FetchContent_MakeAvailable(googletest)
  
  enable_testing()

  file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
  set(
    tests_includes 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SQLPP11_INCLUDE_DIRS}
    ${date_INCLUDE_DIRS}
  )

  # 测试 jwt_manager
  add_executable(jwt_manager_test ${CMAKE_CURRENT_LIST_DIR}/test/gtest/user/jwt_manager_test.cc)
  target_include_directories(jwt_manager_test PRIVATE
    ${tests_includes}
  )
  target_link_libraries(jwt_manager_test PRIVATE
    GTest::gtest_main
    ${libs}
  )

  # 测试 vcode_manager
  add_executable(vcode_manager_test ${CMAKE_CURRENT_LIST_DIR}/test/gtest/user/vcode_manager_test.cc)
  target_include_directories(vcode_manager_test PRIVATE
    ${tests_includes}
  )
  target_link_libraries(vcode_manager_test PRIVATE
    GTest::gtest_main
    ${libs}
  )
  
  include(GoogleTest)
  gtest_add_tests(TARGET jwt_manager_test vcode_manager_test)
endif()

