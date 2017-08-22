#ifndef BKENGINE_TEXT_TEXTURE_BUILDER_H
#define BKENGINE_TEXT_TEXTURE_BUILDER_H

#include <memory>
#include <string>

#include "core/Game.h"
#include "core/TextTexture.h"
#include "exceptions/BuilderException.h"
#include "utils/Geometry.h"


namespace bkengine
{
    class Game;

    class TextTextureBuilder
    {
        friend class TextureBuilder;

    public:
        TextTextureBuilder &setGame(const std::shared_ptr<Game> &);
        TextTextureBuilder &setName(const std::string &);
        TextTextureBuilder &setText(const std::string &);
        TextTextureBuilder &setFontSize(double);
        TextTextureBuilder &setFontName(const std::string &);
        TextTextureBuilder &setTextQuality(TextQuality);
        TextTextureBuilder &setTexturePosition(const Point &);
        TextTextureBuilder &setTextureSize(const RelRect &);
        TextTextureBuilder &setRotation(double);
        TextTextureBuilder &setFlip(bool horizontal, bool vertical);

        std::shared_ptr<Texture> build() const;

    private:
        TextTextureBuilder() = default;

        std::shared_ptr<Game> game = nullptr;
        std::string name;
        std::string text;
        std::string fontName;
        double fontSize;
        TextQuality quality = TextQuality::SOLID;
        Point position = {0, 0};
        Rect textureSize = {0, 0, 100, 100};
        double angleRadians = 0;
        bool flipHorizontally = false;
        bool flipVertically = false;
    };
}

#endif  // BKENGINE_TEXT_TEXTURE_BUILDER_H