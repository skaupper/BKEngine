#ifndef BKENGINE_TEXT_TEXTURE_BUILDER_H
#define BKENGINE_TEXT_TEXTURE_BUILDER_H

#include <memory>
#include <string>

#include "core/Game.h"
#include "core/TextTexture.h"
#include "core/builder/TextureBuilder.h"
#include "exceptions/BuilderException.h"
#include "utils/Geometry.h"


namespace bkengine
{
    class Game;

    class TextTextureBuilder : public TextureBuilder<TextTextureBuilder>
    {
    public:
        TextTextureBuilder &setText(const std::string &);
        TextTextureBuilder &setFontSize(double);
        TextTextureBuilder &setFontName(const std::string &);
        TextTextureBuilder &setTextQuality(TextQuality);

        std::unique_ptr<Texture> build() const;

    private:
        TextTextureBuilder() = default;

        std::string text;
        std::string fontName;
        double fontSize;
        TextQuality quality = TextQuality::SOLID;
    };
}

#endif  // BKENGINE_TEXT_TEXTURE_BUILDER_H