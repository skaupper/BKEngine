#include "catch.hpp"

#include "builder/AnimationBuilder.h"
#include "builder/ElementBuilder.h"
#include "builder/GameBuilder.h"
#include "builder/SceneBuilder.h"
#include "core/utils/GameUtils.h"
#include "core/utils/SceneUtils.h"

#include "MockGraphicsInterface.h"

using namespace bkengine;


TEST_CASE("AnimationBuilder")
{
    SECTION("without anything")
    {
        REQUIRE_THROWS_AS(AnimationBuilder::createBuilder().build<Animation>(), BuilderException);
    }

    SECTION("with parentElement")
    {
        auto gameBuilder = GameBuilder::createBuilder();
        auto game = gameBuilder.setGraphicsInterface<MockGraphicsInterface>().build<Game>();
        auto sceneBuilder = SceneBuilder::createBuilder();
        auto scene = sceneBuilder.setName("test scene").setParentGame(game).build<Scene>();
        auto elementBuilder = ElementBuilder::createBuilder();
        auto element = elementBuilder.setName("test element").setParentScene(scene).build<Element>();

        auto animationBuilder = AnimationBuilder::createBuilder();
        animationBuilder.setName("test animation").setParentElement(element);
        REQUIRE_NOTHROW(animationBuilder.build<Animation>());
    }
}