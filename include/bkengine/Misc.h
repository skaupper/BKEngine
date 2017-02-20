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

        Location() : x(0), y(0) {}
        Location(float x, float y) : x(x), y(y) {}

        std::string toString() const;
        SDL_Point toSDLPoint() const;
    };

    struct Rect {
        float x;
        float y;
        float w;
        float h;

        Rect() : Rect(0, 0) {}
        Rect(float w, float h) : Rect(0, 0, w, h) {}
        Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

        std::string toString() const;
        SDL_Rect toSDLRect() const;
        bool operator==(const Rect &c) const;
        bool operator<(const Rect &c) const;
    };

    struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        Color() : Color(0, 0, 0) {}
        Color(uint8_t r, uint8_t g, uint8_t b) : Color(r, g, b, 0xFF)  {}
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

        std::string toString() const;
        bool operator==(const Color &c) const;
        bool operator<(const Color &c) const;
    };

    enum class TextQuality {
        SOLID = 1,
        BLENDED = 2
    };

    class TextureWrapper
    {
        public:
            explicit TextureWrapper(SDL_Texture *tex);
            virtual ~TextureWrapper();

            SDL_Texture *get() const;
            void set(SDL_Texture *tex);
            void free();

        private:
            SDL_Texture *texture = NULL;
    };
}

#endif
