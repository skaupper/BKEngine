#ifndef BKENGINE_TEXTURE_H
#define BKENGINE_TEXTURE_H

#include <memory>

#include "utils/Geometry.h"


namespace bkengine
{
    class Texture
    {
        friend class TextTextureBuilder;
        friend class ImageTextureBuilder;
        friend class AnimationUtils;

    public:
        virtual ~Texture() = default;

        virtual void onRender() = 0;

        std::string getName() const;

    protected:
        explicit Texture() = default;

        std::string name;
        Rect size;
        Point position;
        double angle;
        bool flipHorizontally;
        bool flipVertically;
    };
}

#endif
