#ifndef BKENGINE_GEOMETRY_H
#define BKENGINE_GEOMETRY_H

#include <string>


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
    };

    struct Size
    {
        double w;
        double h;

        explicit Size();
        Size(double w, double h);

        explicit operator Rect() const;

        std::string toString() const;
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

        /**
            Dummy operator which allows us to use a Rect in a `std::map`.
            Equals to `rect1 != rect2`.
        */
        bool operator<(const Rect &c) const;
    };
}

#endif  // BKENGINE_GEOMETRY_H