cmake_minimum_required(VERSION 3.20)

project(zutil
  VERSION 0.1.0
  LANGUAGES CXX
)

add_library(zutil SHARED
  src/_pro_string.cpp
  src/zassert.cpp
  src/zlog.cpp
  src/ztest.cpp
)

option(ZUTIL_DISABLE_ANSI    "Disable ANSI color output" OFF)
option(ZUTIL_DISABLE_LOGGING "Disable logging subsystem" OFF)
option(ZUTIL_DISABLE_TESTING "Disable internal tests"    OFF)

target_include_directories(zutil
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(zutil PUBLIC cxx_std_23)

target_compile_options(zutil PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

target_compile_definitions(zutil PRIVATE
  $<$<BOOL:${ZUTIL_DISABLE_ANSI}>:Z_DISABLE_ANSI>
  $<$<BOOL:${ZUTIL_DISABLE_LOGGING}>:Z_DISABLE_LOGGING>
  $<$<BOOL:${ZUTIL_DISABLE_TESTING}>:Z_DISABLE_TESTING>
)

set_target_properties(zutil PROPERTIES
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
  POSITION_INDEPENDENT_CODE ON
)

target_compile_definitions(zutil PRIVATE ZUTIL_BUILD)

# --- Testing Library ---
add_executable(zutil_tests src/main.cpp)
target_link_libraries(zutil_tests PRIVATE zutil)
