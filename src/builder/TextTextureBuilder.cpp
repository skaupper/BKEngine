#include "builder/TextTextureBuilder.h"

using namespace bkengine;


TextTextureBuilder &TextTextureBuilder::setGame(const std::shared_ptr<Game> &game)
{
    TextTextureBuilder::game = game;
    return *this;
}

TextTextureBuilder &TextTextureBuilder::setText(const std::string &text)
{
    TextTextureBuilder::text = text;
    return *this;
}

TextTextureBuilder &TextTextureBuilder::setFont(const Font &font)
{
    TextTextureBuilder::font = font;
    return *this;
}

TextTextureBuilder &TextTextureBuilder::setTextureSize(const Rect &textureSize)
{
    TextTextureBuilder::textureSize = textureSize;
    return *this;
}

TextTextureBuilder &TextTextureBuilder::setTextQuality(TextQuality quality)
{
    TextTextureBuilder::quality = quality;
    return *this;
}
