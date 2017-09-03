#ifndef BKENGINE_TEXTURE_H
#define BKENGINE_TEXTURE_H

#include <memory>

#include "core/NameableObject.h"
#include "utils/Geometry.h"


namespace bkengine
{
    class Texture : public NameableObject
    {
        friend class TextTextureBuilder;
        friend class ImageTextureBuilder;
        friend class AnimationUtils;

    public:
        virtual ~Texture() = default;

        virtual void onRender() = 0;

    protected:
        explicit Texture() = default;

        Rect size;
        Point position;
        double angle;
        bool flipHorizontally;
        bool flipVertically;
    };
}

#endif
