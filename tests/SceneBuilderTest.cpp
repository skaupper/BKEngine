#include "catch.hpp"

#include "builder/GameBuilder.h"
#include "builder/SceneBuilder.h"

#include "MockGraphicsInterface.h"

using namespace bkengine;


TEST_CASE("SceneBuilder create Scene")
{
    auto game = GameBuilder::createBuilder().setGraphicsInterface<MockGraphicsInterface>().build<Game>();
    auto builder = SceneBuilder::createBuilder();

    SECTION("with name and parent game")
    {
        builder.setName("builderTest");
        builder.setParentGame(game);
        REQUIRE_NOTHROW(builder.build<Scene>());
    }
    SECTION("with name only")
    {
        builder.setName("builderTest");
        REQUIRE_THROWS_AS(builder.build<Scene>(), BuilderException);
    }
    SECTION("with parent game only")
    {
        builder.setParentGame(game);
        REQUIRE_THROWS_AS(builder.build<Scene>(), BuilderException);
    }
    SECTION("without name and parent game")
    {
        REQUIRE_THROWS_AS(builder.build<Scene>(), BuilderException);
    }
}