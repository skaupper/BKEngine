#ifndef BKENGINE_TEXT_TEXTURE_BUILDER_H
#define BKENGINE_TEXT_TEXTURE_BUILDER_H

#include <memory>
#include <string>

#include "core/Game.h"
#include "utils/Font.h"
#include "utils/Geometry.h"
#include "utils/TextTexture.h"


namespace bkengine
{
    class Game;

    class TextTextureBuilder
    {
        friend class TextureBuilder;

    public:
        TextTextureBuilder &setGame(const std::shared_ptr<Game> &);
        TextTextureBuilder &setText(const std::string &);
        TextTextureBuilder &setFont(const Font &);
        TextTextureBuilder &setTextureSize(const Rect &);
        TextTextureBuilder &setTextQuality(TextQuality);

        template <typename T>
        std::shared_ptr<T> build() const;

    private:
        TextTextureBuilder() = default;

        std::shared_ptr<Game> game;
        std::string text;
        Font font;
        Rect textureSize;
        TextQuality quality;
    };
}

#include "templates/TextTextureBuilder_templates.h"

#endif  // BKENGINE_TEXT_TEXTURE_BUILDER_H