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
    return "<Color {r: " + std::to_string(r) + ", g: " + std::to_string(g)
           + ", b: " + std::to_string(b) + ", a: " + std::to_string(a) + "}>";
}

bool Color::operator==(const Color &c) const
{
    return r == c.r && g == c.g && b == c.b && a == c.a;
}

bool Color::operator!=(const Color &c) const
{
    return !(c == *this);
}

bool Color::operator<(const Color &c) const
{
    return c != *this;
}

Color Colors::BLACK(0, 0, 0);
Color Colors::WHITE(0xff, 0xff, 0xff);
Color Colors::RED(0xff, 0, 0);
Color Colors::LIME(0, 0xff, 0);
Color Colors::BLUE(0, 0, 0xff);
Color Colors::YELLOW(0xff, 0xff, 0);
Color Colors::CYAN(0, 0xff, 0xff);
Color Colors::MAGENTA(0xff, 0, 0xff);
Color Colors::SILVER(0xc0, 0xc0, 0xc0);
Color Colors::GRAY(0x80, 0x80, 0x80);
Color Colors::MAROON(0x80, 0, 0);
Color Colors::OLIVE(0x80, 0x80, 0);
Color Colors::GREEN(0, 0x80, 0);
Color Colors::PURPLE(0x80, 0, 0x80);
Color Colors::TEAL(0, 0x80, 0x80);
Color Colors::NAVY(0, 0, 0x80);