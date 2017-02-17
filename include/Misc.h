#ifndef MISC_H
#define MISC_H

#include <cstdint>

#include "SDLWrapper.h"
#include "Logger.h"


namespace bkengine
{
    struct Location {
        float x;
        float y;

        SDL_Point toSDLPoint();
    };

    struct Rect {
        float x;
        float y;
        float w;
        float h;

        SDL_Rect toSDLRect();
    };

    struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        bool operator==(const Color &c) const;
        bool operator<(const Color &c) const;
    };

    class TextureWrapper
    {
        public:
            explicit TextureWrapper(SDL_Texture *tex);
            virtual ~TextureWrapper();

            SDL_Texture *get();
            void set(SDL_Texture *tex);
            void free();

        private:
            SDL_Texture *texture = NULL;
    };
}

#endif
