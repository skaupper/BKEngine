CMAKE_MINIMUM_REQUIRED (VERSION 2.8.0)
PROJECT (bkengine)

OPTION (ENABLE_TESTS "Set to TRUE if you want to run the testcases afterwards" FALSE)
SET (GMOCK_SOURCE "/usr/src/gmock/gmock-all.cc" CACHE STRING "Path to the gmock-all.cc")
SET (GMOCK_LIBS "" CACHE STRING "Path to the GMock libs")

SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
SET (CMAKE_CXX_STANDARD 14)

FIND_PACKAGE (SDL2 REQUIRED)
FIND_PACKAGE (SDL2_image REQUIRED)
FIND_PACKAGE (SDL2_ttf REQUIRED)
FIND_PACKAGE (SDL2_mixer REQUIRED)

INCLUDE_DIRECTORIES (${SDL2_INCLUDE_DIR}
                     ${SDL2_IMAGE_INCLUDE_DIR}
                     ${SDL2_TTF_INCLUDE_DIR}
                     ${SDL2_MIXER_INCLUDE_DIRS})


SET (SDL_LIBS ${SDL2_LIBRARY}
              ${SDL2_IMAGE_LIBRARIES}
              ${SDL2_TTF_LIBRARIES}
              ${SDL2_MIXER_LIBRARIES})

SET(SOURCES src/Core.cpp
            src/Game.cpp
            src/Timer.cpp
            src/Scene.cpp
            src/Element.cpp
            src/Animation.cpp
            src/Texture.cpp
            src/Scene.cpp
            src/Logger.cpp
            src/Misc.cpp)

IF(ENABLE_TESTS)
    SET (SOURCES ${SOURCES} src/SDLWrapper.cpp)
ENDIF()

# compile library
ADD_LIBRARY (bkengine STATIC ${SOURCES})
TARGET_INCLUDE_DIRECTORIES (bkengine PUBLIC include/ ${SDL2_INCLUDE_DIR}
                     ${SDL2_IMAGE_INCLUDE_DIR}
                     ${SDL2_TTF_INCLUDE_DIR}
                     ${SDL2_MIXER_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES (bkengine ${SDL_LIBS})
TARGET_COMPILE_OPTIONS (bkengine PRIVATE -pedantic -Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-braces)

IF(${ENABLE_TESTS})
    TARGET_COMPILE_DEFINITIONS(bkengine PRIVATE TEST)
    SET (TEST_SOURCES tests/main.cpp
                      tests/CoreTest.cpp
                      tests/TextureTest.cpp)
    IF (NOT GMOCK_LIBS)
        SET (TEST_SOURCES ${TEST_SOURCES} "${GMOCK_SOURCE}")
    ENDIF ()

    ENABLE_TESTING()
    FIND_PACKAGE(GTest REQUIRED)

    # compile test
    ADD_EXECUTABLE (bkengine_tests ${TEST_SOURCES})
    TARGET_INCLUDE_DIRECTORIES (bkengine_tests PRIVATE /usr/src/gmock /usr/src)
    TARGET_LINK_LIBRARIES (bkengine_tests bkengine pthread ${GTEST_BOTH_LIBRARIES})
    IF (GMOCK_LIBS)
        TARGET_LINK_LIBRARIES (bkengine_tests ${GMOCK_LIBS})
    ENDIF ()
    ADD_TEST (NAME Tests COMMAND bkengine_tests)
ENDIF()
