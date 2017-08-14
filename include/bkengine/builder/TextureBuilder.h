#ifndef BKENGINE_TEXTURE_BUILDER_H
#define BKENGINE_TEXTURE_BUILDER_H

#include "builder/ImageTextureBuilder.h"
#include "builder/TextTextureBuilder.h"


namespace bkengine
{
    class ImageTextureBuilder;
    class TextTextureBuilder;

    class TextureBuilder
    {
    public:
        static ImageTextureBuilder createImageBuilder();
        static TextTextureBuilder createTextBuilder();

    private:
        TextureBuilder() = delete;
    };
}

#endif  // BKENGINE_TEXTURE_BUILDER_H