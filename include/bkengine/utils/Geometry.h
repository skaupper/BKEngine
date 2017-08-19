#ifndef BKENGINE_GEOMETRY_H
#define BKENGINE_GEOMETRY_H

#include <cmath>
#include <string>
#include <limits>


namespace bkengine
{
    struct Rect;

    struct Point
    {
        double x;
        double y;

        explicit Point();
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

        explicit Size();
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

        explicit Rect();
        Rect(double w, double h);
        Rect(double x, double y, double w, double h);

        explicit operator Point() const;
        explicit operator Size() const;

        std::string toString() const;

        bool operator==(const Rect &rect) const;
        bool operator!=(const Rect &rect) const;
        bool operator<(const Rect &rect) const;
    };
}

#endif  // BKENGINE_GEOMETRY_H