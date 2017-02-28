#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

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
        public:
            Game(int width, int height, const std::string &title);
            virtual ~Game();

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

            template <typename T> void setEventInterface();
            template <typename T> void setSettingsInterface();
            std::shared_ptr<SettingsInterface> getSettingsInterface();

            template <typename T> T &getData(const std::string &name);
            template <typename T> T &addData(const std::string &name);
            bool hasData(const std::string &name);

            void resizeWindow(int windowWidth, int windowHeight);
            void setWindowTitle(const std::string &);

            void run();
            void stop();

            bool setIcon(const std::string &iconPath);

            void clear();

            virtual void setup();
            virtual void teardown();

        protected:
            std::vector<std::shared_ptr<Scene>> scenes;
            int activeScene;
            bool running;
            Timer timer;
            std::shared_ptr<EventInterface> eventInterface;
            std::shared_ptr<SettingsInterface> settingsInterface;
            std::map<std::string, std::shared_ptr<Storage>> dataStore;

            void onLoop();
            bool onEvent(const Event &);
            void onRender();
    };

#include "templates/Game_templates.h"
}

#endif // GAME_H_INCLUDED
