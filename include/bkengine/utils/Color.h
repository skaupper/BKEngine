#ifndef BKENGINE_COLOR_H
#define BKENGINE_COLOR_H

#include <cstdint>
#include <string>


namespace bkengine
{
    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        Color();
        Color(uint8_t r, uint8_t g, uint8_t b);
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha);

        std::string toString() const;

        bool operator==(const Color &color) const;
        bool operator!=(const Color &color) const;
        bool operator<(const Color &color) const;
    };
}

#endif  // BKENGINE_COLOR_H