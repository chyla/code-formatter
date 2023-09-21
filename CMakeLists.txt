cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)

project(code-formatter
  VERSION 0.0.1
  DESCRIPTION "Code Formatter"
  LANGUAGES CXX
)

option(BUILD_TESTS "BUILD THE TESTS" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(${CMAKE_SOURCE_DIR}/cmake/cppcheck.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/clang_format.cmake)

if (BUILD_TESTS)
    include(${CMAKE_SOURCE_DIR}/cmake/google_test.cmake)
endif()

add_subdirectory(project)
