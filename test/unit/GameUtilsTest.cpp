#include "catch.hpp"

#include "core/builder/GameBuilder.h"
#include "core/builder/SceneBuilder.h"
#include "core/utils/GameUtils.h"
#include "core/utils/SceneUtils.h"

#include "mocks/MockGraphicsInterface.h"

using namespace bkengine;


TEST_CASE("GameUtils")
{
    auto gameBuilder = GameBuilder::createBuilder();
    gameBuilder.setGraphicsInterface<MockGraphicsInterface>();
    auto game = gameBuilder.build<Game>();

    auto sceneName = "GameUtils test scene";
    auto sceneName2 = "GameUtils second test scene";
    auto sceneBuilder = SceneBuilder::createBuilder();
    sceneBuilder.setName(sceneName);
    sceneBuilder.setParentGame(game);

    SECTION("addScene")
    {
        SECTION("add one scene")
        {
            REQUIRE(GameUtils::getSceneCount(game) == 0);
            sceneBuilder.build<Scene>();
            REQUIRE(GameUtils::getSceneCount(game) == 1);
        }
        SECTION("add same scene twice")
        {
            REQUIRE(GameUtils::getSceneCount(game) == 0);
            sceneBuilder.build<Scene>();
            REQUIRE(GameUtils::getSceneCount(game) == 1);
            CHECK_THROWS_AS(sceneBuilder.build<Scene>(), NameAlreadyExistsException);
            REQUIRE(GameUtils::getSceneCount(game) == 1);
        }
        SECTION("add two different named scenes")
        {
            REQUIRE(GameUtils::getSceneCount(game) == 0);
            sceneBuilder.build<Scene>();
            REQUIRE(GameUtils::getSceneCount(game) == 1);
            sceneBuilder.setName(sceneName2);
            CHECK_NOTHROW(sceneBuilder.build<Scene>());
            REQUIRE(GameUtils::getSceneCount(game) == 2);
        }
    }

    SECTION("hasScene")
    {
        SECTION("check for non-existent scene")
        {
            REQUIRE_FALSE(GameUtils::hasScene(game, "arbitrary name"));
            REQUIRE_FALSE(GameUtils::hasScene(game, sceneName));
        }
        SECTION("check for existing scene")
        {
            REQUIRE_FALSE(GameUtils::hasScene(game, sceneName));
            sceneBuilder.build<Scene>();
            REQUIRE(GameUtils::hasScene(game, sceneName));
        }
        SECTION("add two different scenes and check if they exist")
        {
            sceneBuilder.build<Scene>();
            sceneBuilder.setName(sceneName2);
            sceneBuilder.build<Scene>();

            REQUIRE_FALSE(GameUtils::hasScene(game, "GameUtils"));
            REQUIRE_FALSE(GameUtils::hasScene(game, "GameUtils second"));
            REQUIRE(GameUtils::hasScene(game, sceneName));
            REQUIRE(GameUtils::hasScene(game, sceneName2));
        }
    }

    SECTION("removeScene")
    {
        SECTION("non-existent scene")
        {
            REQUIRE_THROWS_AS(GameUtils::removeScene(game, sceneName), NameNotFoundException);
        }
        SECTION("existing scene")
        {
            auto scene = sceneBuilder.build<Scene>();
            REQUIRE(GameUtils::getSceneCount(game) == 1);
            auto removedScene = GameUtils::removeScene(game, sceneName);
            REQUIRE(GameUtils::getSceneCount(game) == 0);
            REQUIRE(scene == removedScene);
        }
        SECTION("two scenes")
        {
            auto scene = sceneBuilder.build<Scene>();
            sceneBuilder.setName(sceneName2);
            auto scene2 = sceneBuilder.build<Scene>();
            REQUIRE(GameUtils::getSceneCount(game) == 2);
            auto removedScene = GameUtils::removeScene(game, sceneName);
            REQUIRE(GameUtils::getSceneCount(game) == 1);
            REQUIRE(scene == removedScene);
            removedScene = GameUtils::removeScene(game, sceneName2);
            REQUIRE(GameUtils::getSceneCount(game) == 0);
            REQUIRE(scene2 == removedScene);
        }
        SECTION("scene twice")
        {
            sceneBuilder.build<Scene>();
            GameUtils::removeScene(game, sceneName);
            REQUIRE(GameUtils::getSceneCount(game) == 0);
            REQUIRE_THROWS_AS(GameUtils::removeScene(game, sceneName), NameNotFoundException);
        }
    }

    SECTION("removeAllScenes")
    {
        SECTION("nothing to be removed")
        {
            REQUIRE(GameUtils::getSceneCount(game) == 0);
            GameUtils::removeAllScenes(game);
            REQUIRE(GameUtils::getSceneCount(game) == 0);
        }
        SECTION("one scene to be removed")
        {
            sceneBuilder.build<Scene>();
            REQUIRE(GameUtils::getSceneCount(game) == 1);
            GameUtils::removeAllScenes(game);
            REQUIRE(GameUtils::getSceneCount(game) == 0);
        }
        SECTION("two scenes to be removed")
        {
            sceneBuilder.build<Scene>();
            sceneBuilder.setName(sceneName2);
            sceneBuilder.build<Scene>();
            REQUIRE(GameUtils::getSceneCount(game) == 2);
            GameUtils::removeAllScenes(game);
            REQUIRE(GameUtils::getSceneCount(game) == 0);
        }
    }

    SECTION("getSceneNames")
    {
        SECTION("no scene added")
        {
            REQUIRE(GameUtils::getSceneCount(game) == 0);
            auto scenes = GameUtils::getSceneNames(game);
            REQUIRE(scenes.size() == 0);
        }
        SECTION("one scene added")
        {
            sceneBuilder.build<Scene>();
            REQUIRE(GameUtils::getSceneCount(game) == 1);
            auto scenes = GameUtils::getSceneNames(game);
            REQUIRE(scenes.size() == 1);
            REQUIRE(scenes.at(0) == sceneName);
        }
        SECTION("two scenes added")
        {
            sceneBuilder.build<Scene>();
            sceneBuilder.setName(sceneName2);
            sceneBuilder.build<Scene>();
            REQUIRE(GameUtils::getSceneCount(game) == 2);
            auto scenes = GameUtils::getSceneNames(game);
            REQUIRE(scenes.size() == 2);
            REQUIRE(scenes.at(0) == sceneName);
            REQUIRE(scenes.at(1) == sceneName2);
        }
    }

    SECTION("getScene")
    {
        SECTION("non-existent scene")
        {
            REQUIRE_THROWS_AS(GameUtils::getScene(game, sceneName), NameNotFoundException);
        }
        SECTION("existing scene")
        {
            auto scene1 = sceneBuilder.build<Scene>();
            sceneBuilder.setName(sceneName2);
            auto scene2 = sceneBuilder.build<Scene>();
            REQUIRE(GameUtils::getSceneCount(game) == 2);
            auto retrievedScene = GameUtils::getScene(game, sceneName);
            REQUIRE(scene1 == retrievedScene);
            retrievedScene = GameUtils::getScene(game, sceneName2);
            REQUIRE(scene2 == retrievedScene);
            REQUIRE(GameUtils::getSceneCount(game) == 2);
        }
    }

    SECTION("getSceneCount")
    {
        // don't know how to test this independently :D
        // gets tested together with other functions (see above)
    }

    SECTION("activateScene")
    {
        SECTION("non-existent scene")
        {
            REQUIRE_THROWS_AS(GameUtils::activateScene(game, sceneName), NameNotFoundException);
        }
        SECTION("existing scene")
        {
            sceneBuilder.build<Scene>();
            REQUIRE_NOTHROW(GameUtils::activateScene(game, sceneName));
        }
    }

    SECTION("getCurrentScene")
    {
        SECTION("no scene activated")
        {
            auto currentScene = GameUtils::getCurrentScene(game);
            REQUIRE(currentScene == nullptr);
        }

        SECTION("two scenes added and first one activated")
        {
            auto scene1 = sceneBuilder.build<Scene>();
            sceneBuilder.setName(sceneName2);
            auto scene2 = sceneBuilder.build<Scene>();
            GameUtils::activateScene(game, sceneName);
            auto currentScene = GameUtils::getCurrentScene(game);
            REQUIRE(currentScene == scene1);
        }

        SECTION("two scenes added and second one activated")
        {
            auto scene1 = sceneBuilder.build<Scene>();
            sceneBuilder.setName(sceneName2);
            auto scene2 = sceneBuilder.build<Scene>();
            GameUtils::activateScene(game, sceneName2);
            auto currentScene = GameUtils::getCurrentScene(game);
            REQUIRE(currentScene == scene2);
        }
    }
}