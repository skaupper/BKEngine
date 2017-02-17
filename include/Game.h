#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <vector>
#include <string>
#include <memory>

#include "Core.h"
#include "Scene.h"
#include "Timer.h"

namespace bkengine
{
    class Scene;

    class Game
    {
        public:
            Game(int width, int height, const std::string &title);
            virtual ~Game();

            void setActiveScene(const std::string &name);
            void setActiveScene(unsigned int index);

            bool hasScene(const std::string &name);
            bool hasScene(unsigned int index);

            void removeScene(const std::string &name);
            void removeScene(unsigned int index);


            template <typename T> T &addScene(const T &);
            template <typename T> T &addScene(const std::shared_ptr<T> &);
            template <typename T, typename... Params> T &addScene(Params...);

            template <typename T> T &getScene(const std::string &name);
            template <typename T, typename... Params> T &getScene(unsigned int index);

            template <typename T> T &getCurrentScene();
            int run();
            void stop();

        private:
            std::vector<std::shared_ptr<Scene>> scenes;
            int activeScene;
            bool running;
            Timer timer;

            void onLoop();
            int onEvent(SDL_Event *);
            void onRender();
    };

#include "templates/Game_templates.h"
}

#endif // GAME_H_INCLUDED
