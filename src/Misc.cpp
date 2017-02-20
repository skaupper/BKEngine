#include "Misc.h"

using namespace bkengine;



std::string Location::toString() const
{
    return "< Location {x: " + std::to_string(x) + ", y: " + std::to_string(x)
           + "} >";
}

SDL_Point Location::toSDLPoint() const
{
    return SDL_Point { (int) x, (int) y };
}

std::string Rect::toString() const
{
    return "< Rect {x: " + std::to_string(x) + ", y: " + std::to_string(x)
           + ", w: " + std::to_string(w) + ", h: " + std::to_string(h) + "} >";
}

SDL_Rect Rect::toSDLRect() const
{
    return SDL_Rect { (int) x, (int) y, (int) w, (int) h };
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

TextureWrapper::TextureWrapper(SDL_Texture *tex)
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
