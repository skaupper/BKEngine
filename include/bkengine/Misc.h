#ifndef MISC_H
#define MISC_H

#include <cstdint>

#include "SDLWrapper.h"
#include "Logger.h"


namespace bkengine
{
    template <typename T> int sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }
    
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

        Rect() : Rect(100, 100) {}
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

    namespace Colors
    {
        extern Color BLACK;
        extern Color WHITE;
        extern Color RED;
        extern Color LIME;
        extern Color BLUE;
        extern Color YELLOW;
        extern Color CYAN;
        extern Color MAGENTA;
        extern Color SILVER;
        extern Color GRAY;
        extern Color MAROON;
        extern Color OLIVE;
        extern Color GREEN;
        extern Color PURPLE;
        extern Color TEAL;
        extern Color NAVY;
    }

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
            Rect getSize() const;

        private:
            SDL_Texture *texture = NULL;
            Rect originalSize;
    };

    class RelativeCoordinates
    {
    public:
        static Rect apply(const Rect &rect, const Rect &srcRect);
    };
}

#endif
