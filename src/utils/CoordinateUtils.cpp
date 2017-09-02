#include "utils/CoordinateUtils.h"

using namespace bkengine;

Rect RelativeCoordinates::apply(const RelRect &rect, const Rect &srcRect)
{
    Rect tmp(srcRect.x + srcRect.w * rect.x / 100,
             srcRect.y + srcRect.h * rect.y / 100,
             srcRect.w * rect.w / 100,
             srcRect.h * rect.h / 100);

    if (srcRect.w == 0) {
        tmp.w = rect.w;
    }

    if (srcRect.h == 0) {
        tmp.h = rect.h;
    }

    return tmp;
}
