#ifndef BKENGINE_GAME_UTILS_H
#define BKENGINE_GAME_UTILS_H

#include <algorithm>
#include <memory>

#include "core/Game.h"
#include "core/Scene.h"
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

        static void activateScene(std::shared_ptr<Game>, const std::string &);

    private:
        GameUtils() = delete;
    };
}

#endif // BKENGINE_GAME_UTILS_H