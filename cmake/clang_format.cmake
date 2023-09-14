find_program(CLANG_FORMAT_BIN NAMES clang-format clang-format-9)

if(CLANG_FORMAT_BIN)
  message(STATUS "Found: clang-format")
  file(GLOB_RECURSE CPP_SOURCE_FILES project/*.cpp)
  file(GLOB_RECURSE CPP_HEADER_FILES project/*.h project/*.hpp)

  add_custom_target(
    format
    COMMENT "Run clang-format..."
    COMMAND ${CLANG_FORMAT_BIN} --style=file -i ${CPP_SOURCE_FILES} ${CPP_HEADER_FILES}
    COMMAND_EXPAND_LISTS VERBATIM
    )
endif()
