find_program(CLANG_FORMAT_BIN
        NAMES clang-format-4.0
        clang-format-3.9
        clang-format-3.8
        clang-format-3.7
        clang-format-3.6
        clang-format
        PATHS ${ClangTools_PATH} $ENV{CLANG_TOOLS_PATH} /usr/local/bin /usr/bin
        NO_DEFAULT_PATH
        )

if ( "${CLANG_FORMAT_BIN}" STREQUAL "CLANG_FORMAT_BIN-NOTFOUND" )
    set(CLANG_FORMAT_FOUND 0)
    message(STATUS "clang-format not found")
else()
    set(CLANG_FORMAT_FOUND 1)
    message(STATUS "clang-format found at ${CLANG_FORMAT_BIN}")
endif()