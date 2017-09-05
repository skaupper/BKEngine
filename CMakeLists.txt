CMAKE_MINIMUM_REQUIRED (VERSION 2.8.0)
PROJECT (bkengine)

SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
SET (CMAKE_CXX_STANDARD 14)

FIND_PACKAGE (SDL2 REQUIRED)
FIND_PACKAGE (SDL2_image REQUIRED)
FIND_PACKAGE (SDL2_ttf REQUIRED)

INCLUDE (ParseAndAddCatchTests)
INCLUDE (prepend)

SET (LIB_INCLUDES ${SDL2_INCLUDE_DIR}
                  ${SDL2_IMAGE_INCLUDE_DIR}
                  ${SDL2_TTF_INCLUDE_DIR})


SET (LIBS ${SDL2_LIBRARY}
          ${SDL2_IMAGE_LIBRARIES}
          ${SDL2_TTF_LIBRARIES})

SET (SOURCES src/core/Game.cpp
             src/core/Scene.cpp
             src/core/Element.cpp
             src/core/Animation.cpp
             src/core/NameableObject.cpp

             src/core/builder/GameBuilder.cpp
             src/core/builder/SceneBuilder.cpp
             src/core/builder/ElementBuilder.cpp
             src/core/builder/AnimationBuilder.cpp
             src/core/builder/TextureBuilder.cpp
             src/core/builder/ImageTextureBuilder.cpp
             src/core/builder/TextTextureBuilder.cpp

             src/interfaces/impl/INISettingsInterface.cpp

             src/utils/Color.cpp
             src/utils/Colors.cpp
             src/utils/Geometry.cpp
             src/utils/CoordinateUtils.cpp
             src/utils/Timer.cpp
             src/utils/Logger.cpp
             src/utils/Event.cpp
             src/utils/Key.cpp
             src/utils/Keys.cpp
             src/utils/InterfaceContainer.cpp
        )

SET(HEADERS include/bkengine/core/builder/templates/AnimationBuilder.tpp
            include/bkengine/core/builder/templates/ElementBuilder.tpp
            include/bkengine/core/builder/templates/GameBuilder.tpp
            include/bkengine/core/builder/templates/SceneBuilder.tpp

            include/bkengine/core/builder/AnimationBuilder.h
            include/bkengine/core/builder/ElementBuilder.h
            include/bkengine/core/builder/GameBuilder.h
            include/bkengine/core/builder/ImageTextureBuilder.h
            include/bkengine/core/builder/SceneBuilder.h
            include/bkengine/core/builder/TextTextureBuilder.h
            include/bkengine/core/builder/TextureBuilder.h

            include/bkengine/core/templates/ActivatorObject.tpp
            include/bkengine/core/templates/HierarchicalObject.tpp

            include/bkengine/core/ActivatableObject.h
            include/bkengine/core/ActivatorObject.h
            include/bkengine/core/Animation.h
            include/bkengine/core/Element.h
            include/bkengine/core/Game.h
            include/bkengine/core/HierarchicalObject.h
            include/bkengine/core/ImageTexture.h
            include/bkengine/core/LazyTextureContainer.h
            include/bkengine/core/NameableObject.h
            include/bkengine/core/Scene.h
            include/bkengine/core/TextTexture.h
            include/bkengine/core/Texture.h

            include/bkengine/exceptions/BuilderException.h
            include/bkengine/exceptions/GameLoopException.h
            include/bkengine/exceptions/IndexOutOfRangeException.h
            include/bkengine/exceptions/NameAlreadyExistsException.h
            include/bkengine/exceptions/NameNotFoundException.h
            include/bkengine/exceptions/NullPointerException.h

            include/bkengine/interfaces/impl/INISettingsInterface.h

            include/bkengine/interfaces/EventInterface.h
            include/bkengine/interfaces/FontInterface.h
            include/bkengine/interfaces/GraphicsInterface.h
            include/bkengine/interfaces/ImageInterface.h
            include/bkengine/interfaces/SettingsInterface.h

            include/bkengine/utils/templates/InterfaceContainer_templates.h

            include/bkengine/utils/backtrace.h
            include/bkengine/utils/Color.h
            include/bkengine/utils/Colors.h
            include/bkengine/utils/CoordinateUtils.h
            include/bkengine/utils/Event.h
            include/bkengine/utils/Geometry.h
            include/bkengine/utils/InterfaceContainer.h
            include/bkengine/utils/Key.h
            include/bkengine/utils/Keys.h
            include/bkengine/utils/Logger.h
            include/bkengine/utils/Timer.h
        )

SET (TEST_SOURCES test/main.cpp
                  test/unit/INISettingsInterfaceTest.cpp
                  test/unit/NameableObjectTest.cpp
                  test/unit/HierarchicalObjectTest.cpp
                  test/unit/ActivatorObjectTest.cpp

#                  test/unit/GameBuilderTest.cpp
#                  test/unit/GameUtilsTest.cpp
#                  test/unit/SceneBuilderTest.cpp
#                  test/unit/ElementBuilderTest.cpp
#                  test/unit/AnimationBuilderTest.cpp
#                  test/unit/ImageTextureBuilderTest.cpp
#                  test/unit/TextTextureBuilderTest.cpp
)

PREPEND(ABSOLUTE_SOURCES ${PROJECT_SOURCE_DIR} ${SOURCES})
PREPEND(ABSOLUTE_HEADERS ${PROJECT_SOURCE_DIR} ${HEADERS})
PREPEND(ABSOLUTE_TEST_SOURCES ${PROJECT_SOURCE_DIR} ${TEST_SOURCES})

# compile library
ADD_LIBRARY (bkengine STATIC ${SOURCES} ${HEADERS})
TARGET_INCLUDE_DIRECTORIES (bkengine PUBLIC include/bkengine ${LIB_INCLUDES})
TARGET_LINK_LIBRARIES (bkengine ${LIBS})
TARGET_COMPILE_OPTIONS (bkengine PRIVATE -pedantic -Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-braces)

# compile tests
ENABLE_TESTING ()

ADD_EXECUTABLE (bkengine_tests ${TEST_SOURCES})
TARGET_INCLUDE_DIRECTORIES(bkengine_tests PRIVATE test/ test/include/)
TARGET_LINK_LIBRARIES (bkengine_tests bkengine)
ADD_CUSTOM_TARGET (check "./bkengine_tests" "--warn" "NoAssertions" WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

ParseAndAddCatchTests (bkengine_tests)

# add a target to reformat source code using clang-format
FIND_PACKAGE (ClangFormat)
IF (CLANG_FORMAT_FOUND)
    INCLUDE (clang-format)
ENDIF (CLANG_FORMAT_FOUND)

# add a target to check sources using cppcheck
FIND_PACKAGE (cppcheck)
IF (CPPCHECK_FOUND)
    INCLUDE (cppcheck)
ENDIF (CPPCHECK_FOUND)

INSTALL (TARGETS bkengine
         ARCHIVE DESTINATION lib)
INSTALL (DIRECTORY include/
         DESTINATION include)
