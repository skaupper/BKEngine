#include "Misc.h"

using namespace bkengine;



std::string Location::toString() const
{
    return "< Location {x: " + std::to_string(x) + ", y: " + std::to_string(y)
           + "} >";
}

SDL_Point Location::toSDLPoint() const
{
    return SDL_Point { (int) round(x), (int) round(y) };
}

std::string Rect::toString() const
{
    return "< Rect {x: " + std::to_string(x) + ", y: " + std::to_string(y)
           + ", w: " + std::to_string(w) + ", h: " + std::to_string(h) + "} >";
}

SDL_Rect Rect::toSDLRect() const
{
    return SDL_Rect { (int) floor(x), (int) floor(y), (int) ceil(w), (int) ceil(h) };
}

bool Rect::operator==(const Rect &r) const
{
    return x == r.x && y == r.y && w == r.w && h == r.h;
}

bool Rect::operator<(const Rect &r) const
{
    return (x + y + w + h) < (r.x + r.y + r.w + r.h);
}

std::string Color::toString() const
{
    return "< Color {r: " + std::to_string(r) + ", g: " + std::to_string(g)
           + ", b: " + std::to_string(b) + ", a: " + std::to_string(a) + "} >";
}

bool Color::operator==(const Color &c) const
{
    return r == c.r && g == c.g && b == c.b && a == c.a;
}

bool Color::operator<(const Color &c) const
{
    return (r + g + b + a) < (c.r + c.g + c.b + c.a);
}

Color Color::BLACK(0, 0, 0);
Color Color::WHITE(0xff, 0xff, 0xff);
Color Color::RED(0xff, 0, 0);
Color Color::LIME(0, 0xff, 0);
Color Color::BLUE(0, 0, 0xff);
Color Color::YELLOW(0xff, 0xff, 0);
Color Color::CYAN(0, 0xff, 0xff);
Color Color::MAGENTA(0xff, 0, 0xff);
Color Color::SILVER(0xc0, 0xc0, 0xc0);
Color Color::GRAY(0x80, 0x80, 0x80);
Color Color::MAROON(0x80, 0, 0);
Color Color::OLIVE(0x80, 0x80, 0);
Color Color::GREEN(0, 0x80, 0);
Color Color::PURPLE(0x80, 0, 0x80);
Color Color::TEAL(0, 0x80, 0x80);
Color Color::NAVY(0, 0, 0x80);

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

Rect TextureWrapper::getSize() const
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
