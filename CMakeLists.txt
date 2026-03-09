cmake_minimum_required(VERSION 3.20)

project(zenutil
  VERSION 0.1.0
  DESCRIPTION "Lightweight C++ utility library"
  LANGUAGES CXX
)

# --------------------------------------------------
# Options
# --------------------------------------------------

option(ZEN_DISABLE_ANSI    "Disable ANSI color output" OFF)
option(ZEN_DISABLE_LOGGING "Disable logging subsystem" OFF)
option(ZEN_DISABLE_TESTING "Disable internal tests"    OFF)

# --------------------------------------------------
# Library
# --------------------------------------------------

add_library(zenutil SHARED
  src/_pro_string.cpp
  src/z_assert.cpp
  src/z_logger.cpp
  src/z_test.cpp
)

add_library(zen::zenutil ALIAS zenutil)

# --------------------------------------------------
# Include directories
# --------------------------------------------------

target_include_directories(zenutil
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# --------------------------------------------------
# Compiler settings
# --------------------------------------------------

target_compile_features(zenutil PUBLIC cxx_std_23)

target_compile_options(zenutil PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

# --------------------------------------------------
# Compile definitions
# --------------------------------------------------

target_compile_definitions(zenutil PRIVATE
  ZEN_BUILD
  $<$<BOOL:${ZEN_DISABLE_ANSI}>:Z_DISABLE_ANSI>
  $<$<BOOL:${ZEN_DISABLE_LOGGING}>:Z_DISABLE_LOGGING>
  $<$<BOOL:${ZEN_DISABLE_TESTING}>:Z_DISABLE_TESTING>
)

# --------------------------------------------------
# Target properties
# --------------------------------------------------

set_target_properties(zenutil PROPERTIES
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
  POSITION_INDEPENDENT_CODE ON
)
