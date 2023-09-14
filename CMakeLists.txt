cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)

project(code-formatter
  VERSION 0.0.1
  DESCRIPTION "Code Formatter"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(${CMAKE_SOURCE_DIR}/cmake/cppcheck.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/clang_format.cmake)

add_subdirectory(external/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
enable_testing()

add_subdirectory(project)
