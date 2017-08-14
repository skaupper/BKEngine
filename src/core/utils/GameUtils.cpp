#include "core/utils/GameUtils.h"

using namespace bkengine;


void GameUtils::addScene(std::shared_ptr<Game> game, std::shared_ptr<Scene> scene)
{
    if (hasScene(game, scene->name)) {
        throw NameAlreadyExistsException("Scene '" + scene->name + "' already exists in game!");
    }

    scene->parentGame = game;
    game->scenes.push_back(scene);
    if (game->currentScene == nullptr) {
        game->currentScene = scene;
    }
}

bool GameUtils::hasScene(std::shared_ptr<Game> game, const std::string &name)
{
    auto findByName = [&name](std::shared_ptr<Scene> scene) { return name == scene->name; };

    auto &scenes = game->scenes;
    auto result = std::find_if(scenes.cbegin(), scenes.cend(), findByName);
    return result != scenes.cend();
}

std::shared_ptr<Scene> GameUtils::removeScene(std::shared_ptr<Game> game, const std::string &name)
{
    auto findByName = [&name](std::shared_ptr<Scene> scene) { return name == scene->name; };

    auto &scenes = game->scenes;
    auto result = std::find_if(scenes.cbegin(), scenes.cend(), findByName);

    if (result == scenes.end()) {
        throw NameNotFoundException("No scene found with the name '" + name + "'!");
    }

    auto scene = *result;
    scenes.erase(result);

    return scene;
}

std::vector<std::shared_ptr<Scene>> GameUtils::removeAllScenes(std::shared_ptr<Game> game)
{
    auto scenesCopy = game->scenes;
    game->scenes.clear();
    return scenesCopy;
}

std::vector<std::string> GameUtils::getSceneNames(std::shared_ptr<Game> game)
{
    auto getName = [](std::shared_ptr<Scene> scene) { return scene->name; };

    std::vector<std::string> nameVector;
    auto &scenes = game->scenes;

    std::transform(scenes.cbegin(), scenes.cend(), std::back_inserter(nameVector), getName);
    return nameVector;
}

std::shared_ptr<Scene> GameUtils::getScene(std::shared_ptr<Game> game, const std::string &name)
{
    auto findByName = [&name](std::shared_ptr<Scene> scene) { return name == scene->name; };

    auto &scenes = game->scenes;
    auto result = std::find_if(scenes.cbegin(), scenes.cend(), findByName);

    if (result == scenes.end()) {
        throw NameNotFoundException("No scene found with the name '" + name + "'!");
    }

    return *result;
}

uint32_t GameUtils::getSceneCount(std::shared_ptr<Game> game)
{
    return game->scenes.size();
}


void GameUtils::activateScene(std::shared_ptr<Game> game, const std::string &name)
{
    auto findByName = [&name](std::shared_ptr<Scene> scene) { return name == scene->name; };

    auto &scenes = game->scenes;
    auto result = std::find_if(scenes.cbegin(), scenes.cend(), findByName);

    if (result == scenes.end()) {
        throw NameNotFoundException("No scene found with the name '" + name + "'!");
    }

    game->currentScene = *result;
}

std::shared_ptr<Scene> GameUtils::getCurrentScene(std::shared_ptr<Game> game)
{
    return game->currentScene;
}