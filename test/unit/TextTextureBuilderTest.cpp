#include "catch.hpp"

#include "core/builder/GameBuilder.h"
#include "core/builder/TextureBuilder.h"

#include "mocks/MockFontInterface.h"
#include "mocks/MockGraphicsInterface.h"

using namespace bkengine;


TEST_CASE("TextTextureBuilder")
{
    auto gameBuilder = GameBuilder::createBuilder();
    gameBuilder.setFontInterface<MockFontInterface>().setGraphicsInterface<MockGraphicsInterface>();
    auto game = gameBuilder.build<Game>();
    TextTextureBuilder builder = TextureBuilder::createTextBuilder();

    SECTION("without game")
    {
        builder.setText("asdf").setFontName("qwer").setFontSize(123);
        builder.setTextureSize({}).setTextQuality(TextQuality::SOLID);
        REQUIRE_THROWS_AS(builder.build(), BuilderException);
    }

    SECTION("without text")
    {
        builder.setGame(game).setFontName("qwer").setFontSize(123);
        builder.setTextureSize({}).setTextQuality(TextQuality::SOLID);
        REQUIRE_THROWS_AS(builder.build(), BuilderException);
    }

    SECTION("without font name")
    {
        builder.setGame(game).setText("qwer").setFontSize(123);
        builder.setTextureSize({}).setTextQuality(TextQuality::SOLID);
        REQUIRE_THROWS_AS(builder.build(), BuilderException);
    }

    SECTION("without font size")
    {
        builder.setGame(game).setText("qwer").setFontName("123");
        builder.setTextureSize({}).setTextQuality(TextQuality::SOLID);
        REQUIRE_THROWS_AS(builder.build(), BuilderException);
    }

    SECTION("defaults")
    {
        builder.setGame(game).setText("qwer").setFontName("123").setFontSize(123).setName("asdf");
        SECTION("default texture quality")
        {
            builder.setTextureSize({});
            REQUIRE_NOTHROW(builder.build());
        }
        SECTION("default texture size")
        {
            builder.setTextQuality(TextQuality::BLENDED);
            REQUIRE_NOTHROW(builder.build());
        }
    }
}