#include "catch.hpp"

#include "core/builder/AnimationBuilder.h"
#include "core/builder/ElementBuilder.h"
#include "core/builder/GameBuilder.h"
#include "core/builder/SceneBuilder.h"
#include "core/builder/TextureBuilder.h"
#include "core/utils/AnimationUtils.h"
#include "core/utils/ElementUtils.h"
#include "core/utils/GameUtils.h"
#include "core/utils/SceneUtils.h"

#include "mocks/MockGraphicsInterface.h"
#include "mocks/MockImageInterface.h"

using namespace bkengine;


TEST_CASE("AnimationUtils")
{
    auto gameBuilder = GameBuilder::createBuilder();
    gameBuilder.setGraphicsInterface<MockGraphicsInterface>().setImageInterface<MockImageInterface>();
    auto game = gameBuilder.build<Game>();
    auto sceneBuilder = SceneBuilder::createBuilder();
    std::string sceneName = "test scene";
    auto scene = sceneBuilder.setName(sceneName).setParentGame(game).build<Scene>();
    auto elementBuilder = ElementBuilder::createBuilder();
    std::string elementName = "test element";
    auto element = elementBuilder.setName(elementName).setParentScene(scene).build<Element>();
    auto animationBuilder = AnimationBuilder::createBuilder();
    std::string animationName = "animationName";
    auto animation = animationBuilder.setName(animationName).setParentElement(element).build<Animation>();

    auto imageInterface = std::make_shared<MockImageInterface>();
    std::string textureName = "test texture";
    auto texBuilder = TextureBuilder::createImageBuilder();
    texBuilder.setName(textureName).setGame(game).setFilePath("asdf");
    auto texture = texBuilder.build();
    auto texture2 = texBuilder.setName("test texture 2").build();

    SECTION("addTexture")
    {
        SECTION("twice the same texture")
        {
            REQUIRE(AnimationUtils::getTextureCount(animation) == 0);
            AnimationUtils::addTexture(animation, texture);
            REQUIRE(AnimationUtils::getTextureCount(animation) == 1);
            CHECK_THROWS_AS(AnimationUtils::addTexture(animation, texture), NameAlreadyExistsException);
            REQUIRE(AnimationUtils::getTextureCount(animation) == 1);
        }
        SECTION("two different textures")
        {
            REQUIRE(AnimationUtils::getTextureCount(animation) == 0);
            AnimationUtils::addTexture(animation, texture);
            REQUIRE(AnimationUtils::getTextureCount(animation) == 1);
            REQUIRE_NOTHROW(AnimationUtils::addTexture(animation, texture2));
            REQUIRE(AnimationUtils::getTextureCount(animation) == 2);
        }
    }

    SECTION("hasTexture")
    {
        SECTION("non-existent texture")
        {
            REQUIRE_FALSE(AnimationUtils::hasTexture(animation, "texture"));
            REQUIRE_FALSE(AnimationUtils::hasTexture(animation, textureName));
        }
        SECTION("existing texture")
        {
            AnimationUtils::addTexture(animation, texture);
            REQUIRE_FALSE(AnimationUtils::hasTexture(animation, "texture"));
            REQUIRE(AnimationUtils::hasTexture(animation, textureName));
        }
    }

    SECTION("removeTexture")
    {
        SECTION("non-existent texture")
        {
            REQUIRE_THROWS_AS(AnimationUtils::removeTexture(animation, "texture"), NameNotFoundException);
            REQUIRE_THROWS_AS(AnimationUtils::removeTexture(animation, textureName), NameNotFoundException);
        }
        SECTION("existing texture")
        {
            AnimationUtils::addTexture(animation, texture);
            AnimationUtils::addTexture(animation, texture2);
            REQUIRE_THROWS_AS(AnimationUtils::removeTexture(animation, "texture"), NameNotFoundException);
            REQUIRE(AnimationUtils::getTextureCount(animation) == 2);
            auto removedTexture = AnimationUtils::removeTexture(animation, textureName);
            REQUIRE(texture == removedTexture);
            REQUIRE(AnimationUtils::getTextureCount(animation) == 1);
        }
    }

    SECTION("removeAllTextures")
    {
        SECTION("empty animation")
        {
            REQUIRE(AnimationUtils::removeAllTextures(animation).size() == 0);
        }
        SECTION("two textures")
        {
            AnimationUtils::addTexture(animation, texture);
            AnimationUtils::addTexture(animation, texture2);
            auto removedTextures = AnimationUtils::removeAllTextures(animation);

            REQUIRE(removedTextures.size() == 2);
            REQUIRE(removedTextures[0] == texture);
            REQUIRE(removedTextures[1] == texture2);
        }
    }

    SECTION("getTexture")
    {
        SECTION("non-existent texture")
        {
            REQUIRE_THROWS_AS(AnimationUtils::getTexture(animation, "test"), NameNotFoundException);
            REQUIRE_THROWS_AS(AnimationUtils::getTexture(animation, textureName), NameNotFoundException);
        }
        SECTION("existing texture")
        {
            AnimationUtils::addTexture(animation, texture);
            AnimationUtils::addTexture(animation, texture2);

            REQUIRE(AnimationUtils::getTexture(animation, textureName) == texture);
            REQUIRE(AnimationUtils::getTexture(animation, "test texture 2") == texture2);
            REQUIRE(AnimationUtils::getTextureCount(animation) == 2);
        }
    }

    SECTION("getTextureNames")
    {
        SECTION("empty animation")
        {
            REQUIRE(AnimationUtils::getTextureNames(animation).size() == 0);
        }
        SECTION("two textures")
        {
            AnimationUtils::addTexture(animation, texture);
            AnimationUtils::addTexture(animation, texture2);

            auto names = AnimationUtils::getTextureNames(animation);
            REQUIRE(names.size() == 2);
            REQUIRE(names[0] == textureName);
            REQUIRE(names[1] == "test texture 2");
        }
    }

    SECTION("getTextureCount")
    {
        // don't know how to test this independently :D
        // gets tested together with other functions (see above)
    }
}