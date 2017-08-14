#ifndef BKENGINE_GAME_UTILS_H
#define BKENGINE_GAME_UTILS_H

#include <algorithm>
#include <memory>

#include "core/Game.h"
#include "core/Scene.h"
#include "exceptions/NameAlreadyExistsException.h"
#include "exceptions/NameNotFoundException.h"


namespace bkengine
{
    class Game;
    class Scene;

    class GameUtils
    {
    public:
        static void addScene(std::shared_ptr<Game>, std::shared_ptr<Scene>);
        static bool hasScene(std::shared_ptr<Game>, const std::string &);
        static std::shared_ptr<Scene> removeScene(std::shared_ptr<Game>, const std::string &);
        static std::vector<std::shared_ptr<Scene>> removeAllScenes(std::shared_ptr<Game>);

        static std::vector<std::string> getSceneNames(std::shared_ptr<Game>);
        static std::shared_ptr<Scene> getScene(std::shared_ptr<Game>, const std::string &);
        static uint32_t getSceneCount(std::shared_ptr<Game>);

        static void activateScene(std::shared_ptr<Game>, const std::string &);
        static std::shared_ptr<Scene> getCurrentScene(std::shared_ptr<Game>);

    private:
        GameUtils() = delete;
    };
}

#endif  // BKENGINE_GAME_UTILS_H