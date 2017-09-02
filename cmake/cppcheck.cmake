add_custom_target(
        cppcheck
        COMMAND ${CPPCHECK_EXECUTABLE}
        --std=c++11
        --enable=warning,style,performance,portability
        -I.
        -Iinclude/bkengine
        ${PROJECT_SOURCE_DIR}/src
        --xml
        --xml-version=2
        --quiet
        2> ${PROJECT_SOURCE_DIR}/cppcheck.xml

        COMMENT "Running cppcheck on ${PROJECT_SOURCE_DIR}/src"
)
