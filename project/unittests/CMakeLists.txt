set(TARGET_NAME code-formatter-unittests)
set(TARGET_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/../include)
set(TARGET_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_executable(${TARGET_NAME} ${TARGET_SOURCES})
target_link_libraries(${TARGET_NAME} gtest)

add_test(${TARGET_NAME} ${TARGET_NAME})
