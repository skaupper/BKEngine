add_custom_target(
        clangformat
        COMMAND ${CLANG_FORMAT_BIN}
        -i
        ${ABSOLUTE_SOURCES}
        ${ABSOLUTE_HEADERS}
        ${ABSOLUTE_TEST_SOURCES}
)
