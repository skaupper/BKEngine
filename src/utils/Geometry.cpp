#include "utils/Geometry.h"

using namespace bkengine;


Point::Point() : x(0), y(0)
{
}

Point::Point(double x, double y) : x(x), y(y)
{
}

Point::operator Rect() const
{
    return {x, y, 0, 0};
}

std::string Point::toString() const
{
    return "<Point {x: " + std::to_string(x) + ", y: " + std::to_string(y) + "}>";
}


Size::Size() : w(0), h(0)
{
}

Size::Size(double w, double h) : w(w), h(h)
{
}

Size::operator Rect() const
{
    return {0, 0, w, h};
}

std::string Size::toString() const
{
    return "<Size {x: " + std::to_string(w) + ", y: " + std::to_string(h) + "}>";
}


Rect::Rect() : Rect(0, 0)
{
}

Rect::Rect(double w, double h) : Rect(0, 0, w, h)
{
}

Rect::Rect(double x, double y, double w, double h) : x(x), y(y), w(w), h(h)
{
}

Rect::operator Point() const
{
    return {x, y};
}

Rect::operator Size() const
{
    return {w, h};
}

std::string Rect::toString() const
{
    return "<Rect {x: " + std::to_string(x) + ", y: " + std::to_string(y) + ", w: " + std::to_string(w)
           + ", h: " + std::to_string(h) + "}>";
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