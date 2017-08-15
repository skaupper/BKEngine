#include "catch.hpp"

#include "builder/ElementBuilder.h"
#include "builder/GameBuilder.h"
#include "builder/SceneBuilder.h"
#include "core/utils/GameUtils.h"
#include "core/utils/SceneUtils.h"

#include "MockGraphicsInterface.h"

using namespace bkengine;

TEST_CASE("ElementBuilder")
{
    SECTION("without anything")
    {
        REQUIRE_THROWS_AS(ElementBuilder::createBuilder().build<Element>(), BuilderException);
    }

    SECTION("with name")
    {
        auto builder = ElementBuilder::createBuilder();
        builder.setName("Element builder");
        REQUIRE_THROWS_AS(builder.build<Element>(), BuilderException);
    }

    SECTION("with name and parent scene")
    {
        auto gameBuilder = GameBuilder::createBuilder();
        auto game = gameBuilder.setGraphicsInterface<MockGraphicsInterface>().build<Game>();
        auto sceneBuilder = SceneBuilder::createBuilder();
        auto scene = sceneBuilder.setName("test scene").setParentGame(game).build<Scene>();

        auto elementBuilder = ElementBuilder::createBuilder();
        REQUIRE_NOTHROW(elementBuilder.setName("test element").setParentScene(scene).build<Element>());
    }
}