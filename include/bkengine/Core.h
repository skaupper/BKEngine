#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include <string>
#include <vector>
#include <functional>

#include "Logger.h"
#include "SDLWrapper.h"


namespace bkengine
{
    enum class FontSize {
        SMALL = 1,
        MEDIUM = 2,
        LARGE = 3
    };

    class Core
    {
        private:
            static Core *instance;
            static bool depsInited;
            static std::vector<std::function<void()>> cleanupFunctions;

            bool inited;

            SDL_Window *window;

            bool isValid;
            int windowHeight;
            int windowWidth;
            std::string windowTitle;
            SDL_Renderer *renderer;


            Core();
            Core(Core &&);
            Core &operator=(Core &&);
            void move(Core &);
            Core(int width, int height, const std::string &windowTitle);

        public:
            static int init();
            static Core *getInstance();
            static Core *getInstance(int width, int height, const std::string &windowTitle);
            static void registerCleanup(std::function<void()>);
            static void quit();

            virtual ~Core();

            int setup();

            SDL_Renderer *getRenderer() const;

            int getWindowHeight() const;
            int getWindowWidth() const;
            std::string getWindowTitle() const;
    };
}

#endif // CORE_H_INCLUDED
