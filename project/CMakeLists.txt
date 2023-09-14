add_subdirectory(unittests)

set(TARGET_NAME code-formatter)
set(TARGET_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TARGET_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_executable(${TARGET_NAME} ${TARGET_SOURCES})
