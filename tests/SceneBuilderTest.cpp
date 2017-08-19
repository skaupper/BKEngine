#include "catch.hpp"

#include "core/builder/GameBuilder.h"
#include "core/builder/SceneBuilder.h"

#include "mocks/MockGraphicsInterface.h"

using namespace bkengine;


TEST_CASE("SceneBuilder")
{
    auto game = GameBuilder::createBuilder().setGraphicsInterface<MockGraphicsInterface>().build<Game>();
    auto builder = SceneBuilder::createBuilder();

    SECTION("with name and parent game")
    {
        builder.setName("core/builderTest");
        builder.setParentGame(game);
        std::shared_ptr<Scene> scene = nullptr;

        REQUIRE_NOTHROW(scene = builder.build<Scene>());

        REQUIRE(scene->getName() == "core/builderTest");
        // TODO: check for parent
    }
    SECTION("with name only")
    {
        builder.setName("core/builderTest");
        std::shared_ptr<Scene> scene = nullptr;

        REQUIRE_NOTHROW(scene = builder.build<Scene>());

        REQUIRE(scene->getName() == "core/builderTest");
        // TODO: check for parent
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