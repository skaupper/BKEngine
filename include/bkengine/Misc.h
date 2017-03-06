#ifndef BKENGINE_MISC_H
#define BKENGINE_MISC_H

#include <cstdint>

#include "SDLWrapper.h"
#include "Logger.h"


namespace bkengine
{
    template <typename T> int sgn(T val)
    {
        return (T(0) < val) - (val < T(0));
    }


    struct Rect;

    struct Location {
        float x;
        float y;

        Location() : x(0), y(0) {}
        Location(float x, float y) : x(x), y(y) {}

        std::string toString() const;
        SDL_Point toSDLPoint() const;

        operator Rect() const;
    };


    struct Size {
        float w;
        float h;

        Size() : w(0), h(0) {}
        Size(float w, float h) : w(w), h(h) {}

        operator Rect() const;

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

        explicit operator Location() const;
        explicit operator Size() const;

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

        static Color BLACK;
        static Color WHITE;
        static Color RED;
        static Color LIME;
        static Color BLUE;
        static Color YELLOW;
        static Color CYAN;
        static Color MAGENTA;
        static Color SILVER;
        static Color GRAY;
        static Color MAROON;
        static Color OLIVE;
        static Color GREEN;
        static Color PURPLE;
        static Color TEAL;
        static Color NAVY;
    };

    enum class TextQuality {
        SOLID = 1,
        BLENDED = 2
    };

    enum class TextureType {
        TEXT,
        IMAGE
    };

    class TextureWrapper
    {
            friend class Texture;
        public:
            explicit TextureWrapper(SDL_Texture *tex, const std::string &path);
            explicit TextureWrapper(SDL_Texture *tex, const std::string &text,
                                    const std::string &fontName, Color c, TextQuality quality);
            virtual ~TextureWrapper();

            SDL_Texture *get() const;
            void set(SDL_Texture *tex);
            void free();
            Rect getSize() const;

        private:
            TextureType type;
            std::string path;
            std::string text;
            std::string fontName;
            Color color;
            TextQuality quality;
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
