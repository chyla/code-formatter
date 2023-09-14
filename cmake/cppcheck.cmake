find_program(CPPCHECK_BIN NAMES cppcheck)

if(CPPCHECK_BIN)
  message(STATUS "Found: cppcheck")
  list(APPEND CMAKE_CXX_CPPCHECK
    "${CPPCHECK_BIN}"
    "--enable=all"
    "--inline-suppr"
    "--check-config"
    "--suppress=missingIncludeSystem"
  )
endif()
