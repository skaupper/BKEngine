#ifndef BKENGINE_TEXTURE_H
#define BKENGINE_TEXTURE_H

#include <memory>

#include "core/NameableObject.h"
#include "utils/Geometry.h"


namespace bkengine
{
    template <typename T>
    class TextureBuilder;
    class TextTextureBuilder;
    class ImageTextureBuilder;

    class Texture : public NameableObject
    {
        friend class TextureBuilder<TextTextureBuilder>;
        friend class TextureBuilder<ImageTextureBuilder>;

    public:
        virtual ~Texture() = default;

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
