#include "catch.hpp"

#include "core/builder/GameBuilder.h"
#include "core/builder/TextureBuilder.h"

#include "mocks/MockGraphicsInterface.h"
#include "mocks/MockImageInterface.h"

using namespace bkengine;


TEST_CASE("ImageTextureBuilder")
{
    auto gameBuilder = GameBuilder::createBuilder();
    gameBuilder.setImageInterface<MockImageInterface>().setGraphicsInterface<MockGraphicsInterface>();
    auto game = gameBuilder.build<Game>();
    ImageTextureBuilder builder = TextureBuilder::createImageBuilder();

    SECTION("without game")
    {
        builder.setTextureSize({}).setClip({}).setFilePath("asdf").setName("asdf");
        REQUIRE_THROWS_AS(builder.build(), BuilderException);
    }

    SECTION("without file path")
    {
        builder.setTextureSize({}).setClip({}).setGame(game).setName("asdf");
        REQUIRE_THROWS_AS(builder.build(), BuilderException);
    }

    SECTION("without name")
    {
        builder.setTextureSize({}).setClip({}).setGame(game).setFilePath("asdf");
        REQUIRE_THROWS_AS(builder.build(), BuilderException);
    }

    SECTION("defaults")
    {
        builder.setGame(game).setFilePath("some path").setName("asdfasdf");
        SECTION("default clip")
        {
            builder.setTextureSize({});
            REQUIRE_NOTHROW(builder.build());
        }
        SECTION("default texture size")
        {
            builder.setClip({});
            REQUIRE_NOTHROW(builder.build());
        }
    }
}