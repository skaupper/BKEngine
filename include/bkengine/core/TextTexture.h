#ifndef BKENGINE_TEXT_TEXTURE
#define BKENGINE_TEXT_TEXTURE

#include "core/Texture.h"


namespace bkengine
{
    enum class TextQuality
    {
        SOLID = 1,
        BLENDED = 2
    };

    class TextTexture : public Texture
    {
        friend class TextTextureBuilder;

    public:
        virtual void onRender() = 0;

    protected:
        explicit TextTexture() = default;

        std::string fontName;
        TextQuality quality;
    };
}

#endif  // BKENGINE_TEXT_TEXTURE