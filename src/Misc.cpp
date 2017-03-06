#include "Misc.h"

using namespace bkengine;

template <typename T> static int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

Point::operator Rect() const
{
    return { x, y, 0, 0 };
}

std::string Point::toString() const
{
    return "<Point {x: " + std::to_string(x) + ", y: " + std::to_string(y)
           + "}>";
}

SDL_Point Point::toSDLPoint() const
{
    return SDL_Point { (int) round(x), (int) round(y) };
}

Size::operator Rect() const
{
    return { 0, 0, w, h };
}

std::string Size::toString() const
{
    return "<Size {x: " + std::to_string(w) + ", y: " + std::to_string(h)
           + "}>";
}

Rect::operator Point() const
{
    return { x, y };
}

Rect::operator Size() const
{
    return { w, h };
}

std::string Rect::toString() const
{
    return "<Rect {x: " + std::to_string(x) + ", y: " + std::to_string(y)
           + ", w: " + std::to_string(w) + ", h: " + std::to_string(h) + "}>";
}

SDL_Rect Rect::toSDLRect() const
{
    return SDL_Rect { (int) floor(x), (int) floor(y), (int) ceil(w), (int) ceil(h) };
}

bool Rect::operator==(const Rect &r) const
{
    return x == r.x && y == r.y && w == r.w && h == r.h;
}

bool Rect::operator!=(const Rect &r) const
{
    return !(r == *this);
}

bool Rect::operator<(const Rect &r) const
{
    return r != *this;
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

TextureWrapper::TextureWrapper(SDL_Texture *tex, const std::string &path) :
    type(TextureType::IMAGE),
    path(path)
{
    set(tex);
}

TextureWrapper::TextureWrapper(SDL_Texture *tex, const std::string &text,
                               const std::string &fontName, Color c,
                               TextQuality quality) :
    type(TextureType::TEXT), text(text), fontName(fontName), color(c),
    quality(quality)
{
    set(tex);
}

TextureWrapper::~TextureWrapper()
{
    free();
}

SDL_Texture *TextureWrapper::get() const
{
    return texture;
}

void TextureWrapper::set(SDL_Texture *tex)
{
    Logger::LogDebug("TextureWrapper::set(SDL_Texture *=" + std::to_string(
                         (unsigned long long int) tex) + ")");
    free();
    texture = tex;
    int w, h;
    MANGLE_SDL(SDL_QueryTexture)(tex, NULL, NULL, &w, &h);
    originalSize = { (float) w, (float) h };
}

void TextureWrapper::free()
{
    if (texture) {
        Logger::LogDebug("TextureWrapper::free(): texture=" + std::to_string(
                             (unsigned long long int) texture));
        MANGLE_SDL(SDL_DestroyTexture)(texture);
        texture = NULL;
    }
}

Size TextureWrapper::getSize() const
{
    return originalSize;
}


Rect RelativeCoordinates::apply(const Rect &rect, const Rect &srcRect)
{
    Rect tmp = { srcRect.x + srcRect.w *rect.x / 100,
                 srcRect.y + srcRect.h *rect.y / 100,
                 srcRect.w *rect.w / 100,
                 srcRect.h *rect.h / 100
               };

    if (srcRect.w == 0) {
        tmp.w = rect.w;
    }

    if (srcRect.h == 0) {
        tmp.h = rect.h;
    }

    return tmp;
}
