#include "catch.hpp"

#include "builder/GameBuilder.h"

#include "MockGraphicsInterface.h"

using namespace bkengine;


TEST_CASE("GameBuilder create Game")
{
    SECTION("without graphics interface")
    {
        REQUIRE_THROWS_AS(GameBuilder::createBuilder().build<Game>(), NullPointerException);
    }

    SECTION("with graphics interface")
    {
        auto builder = GameBuilder::createBuilder();
        builder.setGraphicsInterface<MockGraphicsInterface>();
        REQUIRE_NOTHROW(builder.build<Game>());
    }
}