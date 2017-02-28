#ifndef BKENGINE_GAME_H
#define BKENGINE_GAME_H

#include <vector>
#include <string>
#include <memory>

#include "Core.h"
#include "Scene.h"
#include "Timer.h"
#include "Storage.h"
#include "EventInterface.h"
#include "SettingsInterface.h"


namespace bkengine
{
    class Scene;

    class Game
    {
            /* hierarchal */
        public:
            void activate(const std::string &name);
            void activate(unsigned int index);

            bool hasScene(const std::string &name) const;
            bool hasScene(unsigned int index) const;

            void removeScene(const std::string &name);
            void removeScene(unsigned int index);

            Scene &getScene(const std::string &name);
            Scene &getScene(unsigned int index);
            Scene &getCurrentScene();

            template <typename T> T &addScene(const T &);
            template <typename T> T &addScene(const std::shared_ptr<T> &);
            template <typename T, typename... Params> T &addScene(Params...);
            template <typename T> T &getScene(const std::string &name);
            template <typename T> T &getScene(unsigned int index);
            template <typename T> T &getCurrentScene();

        protected:
            int activeScene;
            std::vector<std::shared_ptr<Scene>> scenes;


            /* getter and setter */
        public:
            bool setIcon(const std::string &iconPath);
            void resizeWindow(int windowWidth, int windowHeight);
            void setWindowTitle(const std::string &);

            template <typename T> void setEventInterface();
            template <typename T> void setSettingsInterface();
            std::shared_ptr<SettingsInterface> getSettingsInterface();

        protected:
            std::shared_ptr<EventInterface> eventInterface;
            std::shared_ptr<SettingsInterface> settingsInterface;


            /* other stuff */
        public:
            Game(int width, int height, const std::string &title);
            virtual ~Game();

            template <typename T> T &getData(const std::string &name);
            template <typename T> T &addData(const std::string &name);
            bool hasData(const std::string &name);

            void run();
            void stop();

            virtual void setup();
            virtual void teardown();

            void clear();

        protected:
            bool running;
            Timer timer;
            std::map<std::string, std::shared_ptr<Storage>> dataStore;

            void onLoop();
            bool onEvent(const Event &);
            void onRender();
    };

#include "templates/Game_templates.h"
}

#endif
