#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include <string>

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
            bool inited;

            SDL_Window *window;
            TTF_Font *largeFont = NULL;
            TTF_Font *mediumFont = NULL;
            TTF_Font *smallFont = NULL;

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
            static void quit();

            virtual ~Core();

            int setup();

            SDL_Renderer *getRenderer();

            int getWindowHeight();
            int getWindowWidth();
            std::string getWindowTitle();

            TTF_Font *getFont(FontSize size);
    };
}

#endif // CORE_H_INCLUDED
