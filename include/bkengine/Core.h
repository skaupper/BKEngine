#ifndef BKENGINE_CORE_H
#define BKENGINE_CORE_H

#include <string>
#include <vector>
#include <functional>

#include "Logger.h"
#include "SDLWrapper.h"
#include "Misc.h"


namespace bkengine
{
    class Core
    {
            /* static stuff */
        public:
            static bool initDeps();
            static Core *getInstance();
            static Core *getInstance(int width, int height, const std::string &windowTitle);
            static void registerCleanup(std::function<void()>);
            static void quit();

        protected:
            static Core *instance;
            static bool depsInited;
            static std::vector<std::function<void()>> cleanupFunctions;


            /* getter and setter */
        public:
            bool setIcon(const std::string &iconPath);
            void setWindowTitle(const std::string &);
            void resizeWindow(int, int);
            Rect getWindowSize();
            std::string getWindowTitle() const;
            SDL_Renderer *getRenderer() const;

        protected:
            std::string windowTitle;
            int windowWidth;
            int windowHeight;


            /* other stuff */
        public:
            virtual ~Core();

            bool initEnvironment();

        protected:
            bool environmentInited;
            SDL_Window *window;
            SDL_Renderer *renderer;

            Core();
            Core(Core &&);
            Core &operator=(Core &&);
            void move(Core &);
            Core(int width, int height, const std::string &windowTitle);
    };
}

#endif
