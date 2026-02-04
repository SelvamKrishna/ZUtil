cmake_minimum_required(VERSION 3.20)

project(zutil
  VERSION 0.1.0
  LANGUAGES CXX
)

add_executable(zutil
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/zansi.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/zlog.cpp
)

target_compile_features(zutil PRIVATE cxx_std_23)
target_include_directories(zutil PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_options(zutil PRIVATE
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)
