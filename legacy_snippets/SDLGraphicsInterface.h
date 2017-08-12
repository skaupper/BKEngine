#ifndef BKENGINE_SDL_GRAPHICSINTERFACE_H
#define BKENGINE_SDL_GRAPHICSINTERFACE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "interfaces/GraphicsInterface.h"


namespace bkengine
{
    class SDLGraphicsInterface : public GraphicsInterface
    {
        public:
            static void initialize();
            static void quit();

            virtual ~SDLGraphicsInterface();

            bool initWindow(int, int, const std::string &) override;
            std::string getLastError() override;

            bool setIcon(const std::string &);

        private:
            struct StaticConstructor {
                StaticConstructor();
            };
            StaticConstructor _;

            SDL_Window *window;
            SDL_Renderer *renderer;
    };
}

#endif