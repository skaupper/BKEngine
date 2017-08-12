#include "catch.hpp"

#include "builder/GameBuilder.h"

using namespace bkengine;


TEST_CASE("GameBuiler empty Game")
{
    SECTION("without graphics interface") {
        REQUIRE_THROWS_AS(GameBuilder::createBuilder().build<Game>(), NullPointerException);
    }
    /*
    SECTION ("with graphics interface") {
        auto builder = GameBuilder::createBuilder();
        builder.setGraphicsInterface<SDLGraphicsInterface>();
        std::shared_ptr<Game> game;
        REQUIRE_NOTHROW(game = builder.build());
        REQUIRE(game != nullptr);
    }
    */
}