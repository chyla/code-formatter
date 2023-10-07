set(PROJECT_DIR ${CMAKE_SOURCE_DIR}/project/)
set(SOURCES_DIR ${PROJECT_DIR}/src/)
set(INCLUDES_DIR ${PROJECT_DIR}/include/)
set(UNITTESTS_DIR ${PROJECT_DIR}/unittests/)

set(FORMATTER_TARGET_NAME formatter-unittests)
set(FORMATTER_TARGET_SOURCES ${UNITTESTS_DIR}/main.cpp
                             ${SOURCES_DIR}/formatter/Formatter.cpp
                             ${SOURCES_DIR}/formatter/detail/InsertNewLineAfterChar.cpp
                             ${CMAKE_CURRENT_SOURCE_DIR}/detail/InsertNewLineAfterCharTests.cpp
                             ${CMAKE_CURRENT_SOURCE_DIR}/FormatterTests.cpp)
add_executable(${FORMATTER_TARGET_NAME} ${FORMATTER_TARGET_SOURCES})
target_link_libraries(${FORMATTER_TARGET_NAME} gtest)
target_include_directories(${FORMATTER_TARGET_NAME} PUBLIC ${INCLUDES_DIR})

add_test(${FORMATTER_TARGET_NAME} ${FORMATTER_TARGET_NAME})
