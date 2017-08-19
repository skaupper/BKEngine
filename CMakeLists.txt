CMAKE_MINIMUM_REQUIRED (VERSION 2.8.0)
PROJECT (bkengine)

SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
SET (CMAKE_CXX_STANDARD 14)

FIND_PACKAGE (SDL2 REQUIRED)
FIND_PACKAGE (SDL2_image REQUIRED)
FIND_PACKAGE (SDL2_ttf REQUIRED)
FIND_PACKAGE (SDL2_mixer REQUIRED)
FIND_PACKAGE (Jsoncpp REQUIRED)

INCLUDE (ParseAndAddCatchTests)   


SET (LIB_INCLUDES ${SDL2_INCLUDE_DIR}
                  ${SDL2_IMAGE_INCLUDE_DIR}
                  ${SDL2_TTF_INCLUDE_DIR}
                  ${SDL2_MIXER_INCLUDE_DIRS}
                  ${JSONCPP_INCLUDE_DIRS})


SET (LIBS ${SDL2_LIBRARY}
          ${SDL2_IMAGE_LIBRARIES}
          ${SDL2_TTF_LIBRARIES}
          ${SDL2_MIXER_LIBRARIES}
          ${JSONCPP_LIBRARIES})

SET (SOURCES src/core/Game.cpp
             src/core/Scene.cpp
             src/core/Element.cpp
             src/core/Animation.cpp
             src/core/Texture.cpp

             src/core/utils/GameUtils.cpp
             src/core/utils/SceneUtils.cpp
             src/core/utils/ElementUtils.cpp
             src/core/utils/AnimationUtils.cpp

             src/builder/GameBuilder.cpp
             src/builder/SceneBuilder.cpp
             src/builder/ElementBuilder.cpp
             src/builder/AnimationBuilder.cpp
             src/builder/TextureBuilder.cpp
             src/builder/ImageTextureBuilder.cpp
             src/builder/TextTextureBuilder.cpp

             src/interfaces/impl/INISettingsInterface.cpp

             src/utils/Color.cpp
             src/utils/Geometry.cpp
             src/utils/CoordinateUtils.cpp
             src/utils/Timer.cpp
             src/utils/Logger.cpp
             src/utils/Event.cpp
             src/utils/Keys.cpp
             src/utils/InterfaceContainer.cpp
)

SET (TEST_SOURCES tests/main.cpp
                  tests/INISettingsInterfaceTest.cpp
                  tests/GameBuilderTest.cpp
                  tests/GameUtilsTest.cpp
                  tests/SceneBuilderTest.cpp
                  tests/SceneUtilsTest.cpp
                  tests/ElementBuilderTest.cpp
                  tests/ElementUtilsTest.cpp
                  tests/AnimationBuilderTest.cpp
                  tests/AnimationUtilsTest.cpp)

# compile library
ADD_LIBRARY (bkengine STATIC ${SOURCES})
TARGET_INCLUDE_DIRECTORIES (bkengine PUBLIC include/bkengine ${LIB_INCLUDES})
TARGET_LINK_LIBRARIES (bkengine ${LIBS})
TARGET_COMPILE_OPTIONS (bkengine PRIVATE -pedantic -Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-braces)

# compile tests
ENABLE_TESTING ()

ADD_EXECUTABLE (bkengine_tests ${TEST_SOURCES})
TARGET_LINK_LIBRARIES (bkengine_tests bkengine)
ADD_CUSTOM_TARGET (check "./bkengine_tests" "--warn" "NoAssertions" "--durations" "yes" WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

ParseAndAddCatchTests (bkengine_tests)

# add a target to generate API documentation with Doxygen
FIND_PACKAGE (Doxygen)
IF (DOXYGEN_FOUND)
    CONFIGURE_FILE (Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    ADD_CUSTOM_TARGET (doc   ${DOXYGEN_EXECUTABLE} 
                             ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                             WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                             COMMENT "Generating API documentation with Doxygen" VERBATIM
                      )
ENDIF (DOXYGEN_FOUND)


INSTALL (TARGETS bkengine
         ARCHIVE DESTINATION lib)
INSTALL (DIRECTORY include/
         DESTINATION include)
