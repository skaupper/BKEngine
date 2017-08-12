#include "core/utils/GameUtils.h"

using namespace bkengine;


void GameUtils::addScene(std::shared_ptr<Game> game, std::shared_ptr<Scene> scene)
{
    scene->parentGame = game;
    game->scenes.push_back(scene);
    if(game->currentScene == nullptr) {
        game->currentScene = scene;
    } 
}

bool GameUtils::hasScene(std::shared_ptr<Game> game, const std::string &name)
{    
    auto findByName = [&name] (std::shared_ptr<Scene> scene) {
        return name == scene->name;
    };
    
    auto scenes = game->scenes;
    auto result = std::find_if(scenes.cbegin(), scenes.cend(), findByName);
    return result != scenes.cend();
}

std::shared_ptr<Scene> GameUtils::removeScene(std::shared_ptr<Game> game, const std::string &name)
{   
    auto findByName = [&name] (std::shared_ptr<Scene> scene) {
        return name == scene->name;
    };
    
    auto scenes = game->scenes;
    auto result = std::find_if(scenes.cbegin(), scenes.cend(), findByName);

    if(result == scenes.end()) {
        throw NameNotFoundException("No scene found with the name '" + name + "'!");
    }

    auto scene = *result;
    scenes.erase(result);

    return scene;
}

void GameUtils::activateScene(std::shared_ptr<Game> game, const std::string &name)
{
    auto findByName = [&name] (std::shared_ptr<Scene> scene) {
        return name == scene->name;
    };
    
    auto scenes = game->scenes;
    auto result = std::find_if(scenes.cbegin(), scenes.cend(), findByName);

    if(result == scenes.end()) {
        throw NameNotFoundException("No scene found with the name '" + name + "'!");
    }

    game->currentScene = *result;
}
