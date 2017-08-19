#ifndef BKENGINE_COORDINATE_UTILS_H
#define BKENGINE_COORDINATE_UTILS_H

#include "utils/Geometry.h"


namespace bkengine
{
    class RelativeCoordinates
    {
    public:
        /**
            Applies relative coordinates to a absolute (or also relative) rectangle.
            Imagine a window with the dimensions 1024:768.
            Applying a (relative) rectangle { 0, 0, 50, 25 } would result in an (absolute) rectangle
            { 0, 0, 512, 192 }.

            \param [in] rect Rectangle with relative coordinates to apply.
            \param [in] srcRect The reference rectangle.

            \return The result of the transformation as Rect.
        */
        static Rect apply(const RelRect &rect, const Rect &srcRect);
    };
}

#endif
