#ifndef BKENGINE_IMAGE_TEXTURE_H
#define BKENGINE_IMAGE_TEXTURE_H

#include "core/Texture.h"


namespace bkengine
{
    class ImageTexture : public Texture
    {
        friend class ImageTextureBuilder;

    public:
        virtual void onRender() = 0;

    protected:
        explicit ImageTexture() = default;

        Rect clip;
    };
}

#endif