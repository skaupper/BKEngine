#ifndef BKENGINE_GEOMETRY_H
#define BKENGINE_GEOMETRY_H

#include <cmath>
#include <limits>
#include <string>


namespace bkengine
{
    struct Rect;

    struct Point
    {
        double x;
        double y;

        // cppcheck-suppress noExplicitConstructor
        Point();
        Point(double x, double y);

        explicit operator Rect() const;

        std::string toString() const;

        bool operator==(const Point &point) const;
        bool operator!=(const Point &point) const;
        bool operator<(const Point &point) const;
    };

    struct Size
    {
        double w;
        double h;

        // cppcheck-suppress noExplicitConstructor
        Size();
        Size(double w, double h);

        explicit operator Rect() const;

        std::string toString() const;

        bool operator==(const Size &size) const;
        bool operator!=(const Size &size) const;
        bool operator<(const Size &size) const;
    };

    struct Rect
    {
        double x;
        double y;
        double w;
        double h;

        // cppcheck-suppress noExplicitConstructor
        Rect();
        Rect(double w, double h);
        Rect(double x, double y, double w, double h);

        explicit operator Point() const;
        explicit operator Size() const;

        std::string toString() const;

        bool operator==(const Rect &rect) const;
        bool operator!=(const Rect &rect) const;
        bool operator<(const Rect &rect) const;
    };

    typedef Rect RelRect;
    typedef Rect AbsRect;
}

#endif  // BKENGINE_GEOMETRY_H