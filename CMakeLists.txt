cmake_minimum_required(VERSION 3.20)

project(zen_util
  VERSION 0.1.0
  LANGUAGES CXX
)

add_library(zen_util SHARED
  src/_pro_string.cpp
  src/z_assert.cpp
  src/z_logger.cpp
  src/z_test.cpp
)

option(ZUTIL_DISABLE_ANSI    "Disable ANSI color output" OFF)
option(ZUTIL_DISABLE_LOGGING "Disable logging subsystem" OFF)
option(ZUTIL_DISABLE_TESTING "Disable internal tests"    OFF)

target_include_directories(zen_util
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(zen_util PUBLIC cxx_std_23)

target_compile_options(zen_util PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

target_compile_definitions(zen_util PRIVATE
  $<$<BOOL:${ZUTIL_DISABLE_ANSI}>:Z_DISABLE_ANSI>
  $<$<BOOL:${ZUTIL_DISABLE_LOGGING}>:Z_DISABLE_LOGGING>
  $<$<BOOL:${ZUTIL_DISABLE_TESTING}>:Z_DISABLE_TESTING>
)

set_target_properties(zen_util PROPERTIES
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
  POSITION_INDEPENDENT_CODE ON
)

target_compile_definitions(zen_util PRIVATE ZUTIL_BUILD)

# --- Testing Library ---
add_executable(zen_testing example/main.cpp)
target_link_libraries(zen_testing PRIVATE zen_util)
