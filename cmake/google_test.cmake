add_subdirectory(${CMAKE_SOURCE_DIR}/external/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
enable_testing()
