#include "core/utils/GameUtils.h"

using namespace bkengine;


void GameUtils::addScene(const std::shared_ptr<Game> &game, const std::shared_ptr<Scene> &scene)
{
    assert(game != nullptr);
    assert(scene != nullptr);

    if (hasScene(game, scene->name)) {
        throw NameAlreadyExistsException("Scene '" + scene->name + "' already exists in game!");
    }

    scene->parentGame = game;
    game->scenes.push_back(scene);
    if (game->currentScene == nullptr) {
        game->currentScene = scene;
    }
}

bool GameUtils::hasScene(const std::shared_ptr<Game> &game, const std::string &name)
{
    assert(game != nullptr);

    auto findByName = [&name](std::shared_ptr<Scene> scene) { return name == scene->name; };

    auto &scenes = game->scenes;
    auto result = std::find_if(scenes.cbegin(), scenes.cend(), findByName);
    return result != scenes.cend();
}

std::shared_ptr<Scene> GameUtils::removeScene(const std::shared_ptr<Game> &game, const std::string &name)
{
    assert(game != nullptr);

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

std::vector<std::shared_ptr<Scene>> GameUtils::removeAllScenes(const std::shared_ptr<Game> &game)
{
    assert(game != nullptr);

    auto scenesCopy = game->scenes;
    game->scenes.clear();
    return scenesCopy;
}

std::vector<std::string> GameUtils::getSceneNames(const std::shared_ptr<Game> &game)
{
    assert(game != nullptr);

    auto getName = [](std::shared_ptr<Scene> scene) { return scene->name; };

    std::vector<std::string> nameVector;
    auto &scenes = game->scenes;

    std::transform(scenes.cbegin(), scenes.cend(), std::back_inserter(nameVector), getName);
    return nameVector;
}

std::shared_ptr<Scene> GameUtils::getScene(const std::shared_ptr<Game> &game, const std::string &name)
{
    assert(game != nullptr);

    auto findByName = [&name](std::shared_ptr<Scene> scene) { return name == scene->name; };

    auto &scenes = game->scenes;
    auto result = std::find_if(scenes.cbegin(), scenes.cend(), findByName);

    if (result == scenes.end()) {
        throw NameNotFoundException("No scene found with the name '" + name + "'!");
    }

    return *result;
}

uint32_t GameUtils::getSceneCount(const std::shared_ptr<Game> &game)
{
    assert(game != nullptr);

    return game->scenes.size();
}


void GameUtils::activateScene(const std::shared_ptr<Game> &game, const std::string &name)
{
    assert(game != nullptr);

    auto findByName = [&name](std::shared_ptr<Scene> scene) { return name == scene->name; };

    auto &scenes = game->scenes;
    auto result = std::find_if(scenes.cbegin(), scenes.cend(), findByName);

    if (result == scenes.end()) {
        throw NameNotFoundException("No scene found with the name '" + name + "'!");
    }

    game->currentScene = *result;
}

std::shared_ptr<Scene> GameUtils::getCurrentScene(const std::shared_ptr<Game> &game)
{
    assert(game != nullptr);

    return game->currentScene;
}