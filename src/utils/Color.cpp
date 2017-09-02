#include "utils/Color.h"

using namespace bkengine;

Color::Color() : Color(0, 0, 0)
{
}

Color::Color(uint8_t r, uint8_t g, uint8_t b) : Color(r, g, b, 0xFF)
{
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a)
{
}

std::string Color::toString() const
{
    return "<Color {r: " + std::to_string(r) + ", g: " + std::to_string(g) + ", b: " + std::to_string(b) + ", a: "
           + std::to_string(a) + "}>";
}

bool Color::operator==(const Color &c) const
{
    return r == c.r && g == c.g && b == c.b && a == c.a;
}

bool Color::operator!=(const Color &c) const
{
    return !(operator==(c));
}

bool Color::operator<(const Color &c) const
{
    if (r == c.r) {
        if (g == c.g) {
            if (b == c.b) {
                return false;
            }
            return b < c.b;
        }
        return g < c.g;
    }
    return r < c.r;
}
