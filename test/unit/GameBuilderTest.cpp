#include "catch.hpp"

#include "core/builder/GameBuilder.h"

#include "mocks/MockGraphicsInterface.h"

using namespace bkengine;


TEST_CASE("GameBuilder")
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