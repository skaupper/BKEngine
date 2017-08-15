#include "catch.hpp"

#include "builder/ElementBuilder.h"
#include "builder/GameBuilder.h"
#include "builder/SceneBuilder.h"
#include "core/utils/GameUtils.h"
#include "core/utils/SceneUtils.h"

#include "MockGraphicsInterface.h"

using namespace bkengine;

TEST_CASE("SceneUtilsTest.cpp")
{
    auto gameBuilder = GameBuilder::createBuilder();
    auto game = gameBuilder.setGraphicsInterface<MockGraphicsInterface>().build<Game>();
    auto sceneBuilder = SceneBuilder::createBuilder();
    std::string sceneName = "test scene";
    auto scene = sceneBuilder.setName(sceneName).setParentGame(game).build<Scene>();
    auto elementBuilder = ElementBuilder::createBuilder();
    std::string elementName = "test element";
    elementBuilder.setName(elementName).setParentScene(scene);

    SECTION("addElement")
    {
        SECTION("twice the same element")
        {
            REQUIRE(SceneUtils::getElementCount(scene) == 0);
            elementBuilder.build<Element>();
            REQUIRE(SceneUtils::getElementCount(scene) == 1);
            CHECK_THROWS_AS(elementBuilder.build<Element>(), NameAlreadyExistsException);
            REQUIRE(SceneUtils::getElementCount(scene) == 1);
        }
        SECTION("two different elements")
        {
            REQUIRE(SceneUtils::getElementCount(scene) == 0);
            elementBuilder.build<Element>();
            REQUIRE(SceneUtils::getElementCount(scene) == 1);
            REQUIRE_NOTHROW(elementBuilder.setName("test element 2").build<Element>());
            REQUIRE(SceneUtils::getElementCount(scene) == 2);
        }
    }

    SECTION("hasElement")
    {
        SECTION("non-existent element")
        {
            REQUIRE_FALSE(SceneUtils::hasElement(scene, "element"));
            REQUIRE_FALSE(SceneUtils::hasElement(scene, elementName));
        }
        SECTION("existing element")
        {
            elementBuilder.build<Element>();
            REQUIRE_FALSE(SceneUtils::hasElement(scene, "element"));
            REQUIRE(SceneUtils::hasElement(scene, elementName));
        }
    }

    SECTION("removeElement")
    {
        SECTION("non-existent element")
        {
            REQUIRE_THROWS_AS(SceneUtils::removeElement(scene, "element"), NameNotFoundException);
            REQUIRE_THROWS_AS(SceneUtils::removeElement(scene, elementName), NameNotFoundException);
        }
        SECTION("existing element")
        {
            auto element = elementBuilder.build<Element>();
            elementBuilder.setName("test element 2").build<Element>();
            REQUIRE_THROWS_AS(SceneUtils::removeElement(scene, "element"), NameNotFoundException);
            REQUIRE(SceneUtils::getElementCount(scene) == 2);
            auto removedElement = SceneUtils::removeElement(scene, elementName);
            REQUIRE(element == removedElement);
            REQUIRE(SceneUtils::getElementCount(scene) == 1);
        }
    }

    SECTION("removeAllElements")
    {
        SECTION("empty scene")
        {
            REQUIRE(SceneUtils::removeAllElements(scene).size() == 0);
        }
        SECTION("two elements")
        {
            auto element = elementBuilder.build<Element>();
            auto element2 = elementBuilder.setName("test element 2").build<Element>();
            auto removedElements = SceneUtils::removeAllElements(scene);

            REQUIRE(removedElements.size() == 2);
            REQUIRE(removedElements[0] == element);
            REQUIRE(removedElements[1] == element2);
        }
    }

    SECTION("getElement")
    {
        SECTION("non-existent element")
        {
            REQUIRE_THROWS_AS(SceneUtils::getElement(scene, "test"), NameNotFoundException);
            REQUIRE_THROWS_AS(SceneUtils::getElement(scene, elementName), NameNotFoundException);
        }
        SECTION("existing element")
        {
            auto element = elementBuilder.build<Element>();
            auto element2 = elementBuilder.setName("test element 2").build<Element>();

            REQUIRE(SceneUtils::getElement(scene, elementName) == element);
            REQUIRE(SceneUtils::getElement(scene, "test element 2") == element2);
            REQUIRE(SceneUtils::getElementCount(scene) == 2);
        }
    }

    SECTION("getElementNames")
    {
        SECTION("empty scene")
        {
            REQUIRE(SceneUtils::getElementNames(scene).size() == 0);
        }
        SECTION("two elements")
        {
            auto element = elementBuilder.build<Element>();
            auto element2 = elementBuilder.setName("test element 2").build<Element>();

            auto names = SceneUtils::getElementNames(scene);
            REQUIRE(names.size() == 2);
            REQUIRE(names[0] == elementName);
            REQUIRE(names[1] == "test element 2");
        }
    }

    SECTION("getElementCount")
    {
        // don't know how to test this independently :D
        // gets tested together with other functions (see above)
    }

    SECTION("getCollisionLayer")
    {
        SECTION("empty layer")
        {
            REQUIRE(SceneUtils::getCollisionLayer(scene, 0).size() == 0);
        }

        SECTION("one layer with one and one with two elements")
        {
            auto element = elementBuilder.build<Element>();
            auto element2 = elementBuilder.setName("test element 2").build<Element>();
            auto element3 = elementBuilder.setName("test element 3").setCollisionLayer(1).build<Element>();

            auto layer0 = SceneUtils::getCollisionLayer(scene, 0);
            auto layer1 = SceneUtils::getCollisionLayer(scene, 1);
            auto layer2 = SceneUtils::getCollisionLayer(scene, 2);

            REQUIRE(layer0.size() == 2);
            REQUIRE(layer0[0] == element);
            REQUIRE(layer0[1] == element2);

            REQUIRE(layer1.size() == 1);
            REQUIRE(layer1[0] == element3);

            REQUIRE(layer2.size() == 0);
        }
    }

    SECTION("getCollisionLayerOfElement")
    {
        SECTION("one layer with one and one with two elements")
        {
            auto element = elementBuilder.build<Element>();
            auto element2 = elementBuilder.setName("test element 2").build<Element>();
            auto element3 = elementBuilder.setName("test element 3").setCollisionLayer(1).build<Element>();

            auto layerOfElement = SceneUtils::getCollisionLayerOfElement(scene, element);
            auto layerOfElement2 = SceneUtils::getCollisionLayerOfElement(scene, element2);
            auto layerOfElement3 = SceneUtils::getCollisionLayerOfElement(scene, element3);

            REQUIRE(layerOfElement.size() == 1);
            REQUIRE(layerOfElement[0] == element2);

            REQUIRE(layerOfElement2.size() == 1);
            REQUIRE(layerOfElement2[0] == element);

            REQUIRE(layerOfElement3.size() == 0);
        }
    }

    SECTION("moveElementToCollisionLayer")
    {
        SECTION("one layer with one and one with two elements")
        {
            auto element = elementBuilder.build<Element>();
            auto element2 = elementBuilder.setName("test element 2").build<Element>();
            auto element3 = elementBuilder.setName("test element 3").setCollisionLayer(1).build<Element>();

            auto layer0 = SceneUtils::getCollisionLayer(scene, 0);
            auto layer1 = SceneUtils::getCollisionLayer(scene, 1);
            auto layer2 = SceneUtils::getCollisionLayer(scene, 2);

            REQUIRE(layer0.size() == 2);
            REQUIRE(layer1.size() == 1);
            REQUIRE(layer2.size() == 0);

            SceneUtils::moveElementToCollisionLayer(scene, elementName, 2);
            SceneUtils::moveElementToCollisionLayer(scene, "test element 3", 2);

            layer0 = SceneUtils::getCollisionLayer(scene, 0);
            layer1 = SceneUtils::getCollisionLayer(scene, 1);
            layer2 = SceneUtils::getCollisionLayer(scene, 2);

            REQUIRE(layer0.size() == 1);
            REQUIRE(layer1.size() == 0);
            REQUIRE(layer2.size() == 2);
        }
    }
}