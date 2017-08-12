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

    public:
        virtual ~Texture() = default;

        virtual void onRender() = 0;


    protected:
        explicit Texture() = default;

        Rect size;
    };
}

#endif
