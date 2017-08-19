#include "utils/Geometry.h"

using namespace bkengine;


static int8_t doubleCompare(double d1, double d2)
{
    static double EPSILON = std::numeric_limits<double>::epsilon();

    double diff = std::fabs(d1 - d2);

    if (diff < EPSILON) {
        return 0;
    }

    if (d1 < d2) {
        return -1;
    }

    return 1;
}


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

bool Point::operator==(const Point &point) const
{
    bool equalX = (doubleCompare(x, point.x) == 0);
    bool equalY = (doubleCompare(y, point.y) == 0);
    return equalX && equalY;
}

bool Point::operator!=(const Point &point) const
{
    return !(operator==(point));
}

bool Point::operator<(const Point &point) const
{
    int8_t cmp;
    if ((cmp = doubleCompare(x, point.x)) == 1) {
        return true;
    } else if (cmp == -1) {
        return false;
    }

    if ((cmp = doubleCompare(y, point.y)) == 1) {
        return true;
    } else if (cmp == -1) {
        return false;
    }

    return false;
}


Size::Size() : w(100), h(100)
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

bool Size::operator==(const Size &size) const
{
    bool equalW = (doubleCompare(w, size.w) == 0);
    bool equalH = (doubleCompare(h, size.h) == 0);
    return equalW && equalH;
}

bool Size::operator!=(const Size &size) const
{
    return !(operator==(size));
}

bool Size::operator<(const Size &size) const
{
    int8_t cmp;
    if ((cmp = doubleCompare(w, size.w)) == 1) {
        return true;
    } else if (cmp == -1) {
        return false;
    }

    if ((cmp = doubleCompare(h, size.h)) == 1) {
        return true;
    } else if (cmp == -1) {
        return false;
    }

    return false;
}


Rect::Rect() : Rect(100, 100)
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
    bool equalX = (doubleCompare(x, r.x) == 0);
    bool equalY = (doubleCompare(y, r.y) == 0);
    bool equalW = (doubleCompare(w, r.w) == 0);
    bool equalH = (doubleCompare(h, r.h) == 0);
    return equalX && equalY && equalW && equalH;
}

bool Rect::operator!=(const Rect &r) const
{
    return !(operator==(r));
}

bool Rect::operator<(const Rect &r) const
{
    int8_t cmp;
    if ((cmp = doubleCompare(x, r.x)) == 1) {
        return true;
    } else if (cmp == -1) {
        return false;
    }

    if ((cmp = doubleCompare(y, r.y)) == 1) {
        return true;
    } else if (cmp == -1) {
        return false;
    }

    if ((cmp = doubleCompare(w, r.w)) == 1) {
        return true;
    } else if (cmp == -1) {
        return false;
    }

    if ((cmp = doubleCompare(h, r.h)) == 1) {
        return true;
    } else if (cmp == -1) {
        return false;
    }

    return false;
}