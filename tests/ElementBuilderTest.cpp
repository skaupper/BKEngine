#include "catch.hpp"

#include "core/builder/ElementBuilder.h"
#include "core/builder/GameBuilder.h"
#include "core/builder/SceneBuilder.h"
#include "core/utils/GameUtils.h"
#include "core/utils/SceneUtils.h"

#include "mocks/MockGraphicsInterface.h"

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
        std::shared_ptr<Element> element = nullptr;
        REQUIRE_NOTHROW(element = builder.build<Element>());

        REQUIRE(element->getName() == "Element builder");
    }

    SECTION("with name and parent scene")
    {
        auto gameBuilder = GameBuilder::createBuilder();
        auto game = gameBuilder.setGraphicsInterface<MockGraphicsInterface>().build<Game>();
        auto sceneBuilder = SceneBuilder::createBuilder();
        auto scene = sceneBuilder.setName("test scene").setParentGame(game).build<Scene>();

        auto elementBuilder = ElementBuilder::createBuilder();
        elementBuilder.setName("test element").setParentScene(scene);
        std::shared_ptr<Element> element = nullptr;
        REQUIRE_NOTHROW(element = elementBuilder.build<Element>());
        REQUIRE(element->getName() == "test element");
        REQUIRE(element->getCollisionBox() == RelRect(0, 0, 100, 100));
        REQUIRE(element->getRenderBox() == RelRect(0, 0, 100, 100));
    }
}