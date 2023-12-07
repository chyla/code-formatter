set(PROJECT_DIR ${CMAKE_SOURCE_DIR}/project/)
set(SOURCES_DIR ${PROJECT_DIR}/src/)
set(INCLUDES_DIR ${PROJECT_DIR}/include/)

set(TARGET_NAME code-formatter)
set(TARGET_SOURCES ${SOURCES_DIR}/main.cpp
                   ${SOURCES_DIR}/formatter/Formatter.cpp
                   ${SOURCES_DIR}/formatter/detail/InsertNewLineAfterChar.cpp
                   ${SOURCES_DIR}/formatter/detail/UpdateIndentation.cpp
                   )

add_executable(${TARGET_NAME} ${TARGET_SOURCES})
target_include_directories(${TARGET_NAME} PUBLIC ${INCLUDES_DIR})
