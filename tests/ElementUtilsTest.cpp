#include "catch.hpp"

#include "builder/AnimationBuilder.h"
#include "builder/ElementBuilder.h"
#include "builder/GameBuilder.h"
#include "builder/SceneBuilder.h"
#include "core/utils/ElementUtils.h"
#include "core/utils/GameUtils.h"
#include "core/utils/SceneUtils.h"

#include "MockGraphicsInterface.h"

using namespace bkengine;


TEST_CASE("ElementUtils")
{
    auto gameBuilder = GameBuilder::createBuilder();
    auto game = gameBuilder.setGraphicsInterface<MockGraphicsInterface>().build<Game>();
    auto sceneBuilder = SceneBuilder::createBuilder();
    std::string sceneName = "test scene";
    auto scene = sceneBuilder.setName(sceneName).setParentGame(game).build<Scene>();
    auto elementBuilder = ElementBuilder::createBuilder();
    std::string elementName = "test element";
    auto element = elementBuilder.setName(elementName).setParentScene(scene).build<Element>();
    auto animationBuilder = AnimationBuilder::createBuilder();
    std::string animationName = "animationName";
    animationBuilder.setName(animationName).setParentElement(element);

    SECTION("addAnimation")
    {
        SECTION("twice the same animation")
        {
            REQUIRE(ElementUtils::getAnimationCount(element) == 0);
            animationBuilder.build<Animation>();
            REQUIRE(ElementUtils::getAnimationCount(element) == 1);
            CHECK_THROWS_AS(animationBuilder.build<Animation>(), NameAlreadyExistsException);
            REQUIRE(ElementUtils::getAnimationCount(element) == 1);
        }
        SECTION("two different animations")
        {
            REQUIRE(ElementUtils::getAnimationCount(element) == 0);
            animationBuilder.build<Animation>();
            REQUIRE(ElementUtils::getAnimationCount(element) == 1);
            REQUIRE_NOTHROW(animationBuilder.setName("test animation 2").build<Animation>());
            REQUIRE(ElementUtils::getAnimationCount(element) == 2);
        }
    }

    SECTION("hasAnimation")
    {
        SECTION("non-existent animation")
        {
            REQUIRE_FALSE(ElementUtils::hasAnimation(element, "animation"));
            REQUIRE_FALSE(ElementUtils::hasAnimation(element, animationName));
        }
        SECTION("existing animation")
        {
            animationBuilder.build<Animation>();
            REQUIRE_FALSE(ElementUtils::hasAnimation(element, "animation"));
            REQUIRE(ElementUtils::hasAnimation(element, animationName));
        }
    }

    SECTION("removeAnimation")
    {
        SECTION("non-existent animation")
        {
            REQUIRE_THROWS_AS(ElementUtils::removeAnimation(element, "animation"), NameNotFoundException);
            REQUIRE_THROWS_AS(ElementUtils::removeAnimation(element, animationName), NameNotFoundException);
        }
        SECTION("existing animation")
        {
            auto animation = animationBuilder.build<Animation>();
            animationBuilder.setName("test animation 2").build<Animation>();
            REQUIRE_THROWS_AS(ElementUtils::removeAnimation(element, "animation"), NameNotFoundException);
            REQUIRE(ElementUtils::getAnimationCount(element) == 2);
            auto removedElement = ElementUtils::removeAnimation(element, animationName);
            REQUIRE(animation == removedElement);
            REQUIRE(ElementUtils::getAnimationCount(element) == 1);
        }
    }

    SECTION("removeAllAnimations")
    {
        SECTION("empty element")
        {
            REQUIRE(ElementUtils::removeAllAnimations(element).size() == 0);
        }
        SECTION("two animations")
        {
            auto animation = animationBuilder.build<Animation>();
            auto animation2 = animationBuilder.setName("test animation 2").build<Animation>();
            auto removedElements = ElementUtils::removeAllAnimations(element);

            REQUIRE(removedElements.size() == 2);
            REQUIRE(removedElements[0] == animation);
            REQUIRE(removedElements[1] == animation2);
        }
    }

    SECTION("getAnimation")
    {
        SECTION("non-existent animation")
        {
            REQUIRE_THROWS_AS(ElementUtils::getAnimation(element, "test"), NameNotFoundException);
            REQUIRE_THROWS_AS(ElementUtils::getAnimation(element, animationName), NameNotFoundException);
        }
        SECTION("existing animation")
        {
            auto animation = animationBuilder.build<Animation>();
            auto animation2 = animationBuilder.setName("test animation 2").build<Animation>();

            REQUIRE(ElementUtils::getAnimation(element, animationName) == animation);
            REQUIRE(ElementUtils::getAnimation(element, "test animation 2") == animation2);
            REQUIRE(ElementUtils::getAnimationCount(element) == 2);
        }
    }

    SECTION("getAnimationNames")
    {
        SECTION("empty element")
        {
            REQUIRE(ElementUtils::getAnimationNames(element).size() == 0);
        }
        SECTION("two animations")
        {
            auto animation = animationBuilder.build<Animation>();
            auto animation2 = animationBuilder.setName("test animation 2").build<Animation>();

            auto names = ElementUtils::getAnimationNames(element);
            REQUIRE(names.size() == 2);
            REQUIRE(names[0] == animationName);
            REQUIRE(names[1] == "test animation 2");
        }
    }

    SECTION("getAnimationCount")
    {
        // don't know how to test this independently :D
        // gets tested together with other functions (see above)
    }

    SECTION("activateAnimation")
    {
        SECTION("non-existent animation")
        {
            REQUIRE_THROWS_AS(ElementUtils::activateAnimation(element, "test"), NameNotFoundException);
            REQUIRE_THROWS_AS(ElementUtils::activateAnimation(element, animationName), NameNotFoundException);
        }
        SECTION("existing animation")
        {
            auto animation = animationBuilder.build<Animation>();
            auto animation2 = animationBuilder.setName("test animation 2").build<Animation>();

            REQUIRE_NOTHROW(ElementUtils::activateAnimation(element, animationName));
            REQUIRE_NOTHROW(ElementUtils::activateAnimation(element, "test animation 2"));
            REQUIRE(ElementUtils::getAnimationCount(element) == 2);
        }
    }
}