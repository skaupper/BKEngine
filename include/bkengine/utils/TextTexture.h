#ifndef BKENGINE_TEXT_TEXTURE
#define BKENGINE_TEXT_TEXTURE

#include "core/Texture.h"
#include "utils/Font.h"


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

        Font font;
        TextQuality quality;
    };
}

#endif  // BKENGINE_TEXT_TEXTURE