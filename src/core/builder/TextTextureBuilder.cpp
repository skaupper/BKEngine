#include "core/builder/TextTextureBuilder.h"

using namespace bkengine;


TextTextureBuilder &TextTextureBuilder::setGame(const std::shared_ptr<Game> &game)
{
    TextTextureBuilder::game = game;
    return *this;
}

TextTextureBuilder &TextTextureBuilder::setName(const std::string &name)
{
    TextTextureBuilder::name = name;
    return *this;
}

TextTextureBuilder &TextTextureBuilder::setText(const std::string &text)
{
    TextTextureBuilder::text = text;
    return *this;
}

TextTextureBuilder &TextTextureBuilder::setFontName(const std::string &name)
{
    fontName = name;
    return *this;
}

TextTextureBuilder &TextTextureBuilder::setFontSize(double size)
{
    fontSize = size;
    return *this;
}

TextTextureBuilder &TextTextureBuilder::setTextQuality(TextQuality quality)
{
    TextTextureBuilder::quality = quality;
    return *this;
}

TextTextureBuilder &TextTextureBuilder::setTexturePosition(const Point &position)
{
    TextTextureBuilder::position = position;
    return *this;
}

TextTextureBuilder &TextTextureBuilder::setTextureSize(const RelRect &textureSize)
{
    TextTextureBuilder::textureSize = textureSize;
    return *this;
}

TextTextureBuilder &TextTextureBuilder::setRotation(double angle)
{
    angleRadians = angle;
    return *this;
}

TextTextureBuilder &TextTextureBuilder::setFlip(bool horizontal, bool vertical)
{
    flipHorizontally = horizontal;
    flipVertically = vertical;
    return *this;
}


std::shared_ptr<Texture> TextTextureBuilder::build() const
{
    if (game == nullptr) {
        throw BuilderException("You have to set the target game for the texture!");
    }

    if (name.empty()) {
        throw BuilderException("You have to specify a name for the texture!");
    }

    if (fontName.empty()) {
        throw BuilderException("Empty font names are not allowed!");
    }

    if (text.empty()) {
        throw BuilderException("An empty text cannot be rendered!");
    }

    if (fontSize < std::numeric_limits<double>::epsilon()) {
        throw BuilderException("The font size has to be set to a value greater than 0!");
    }

    auto fontInterface = game->interfaceContainer.getFontInterface();
    if (fontInterface == nullptr) {
        throw BuilderException("The given game has to have a font interface set!");
    }

    std::shared_ptr<Texture> texture = fontInterface->renderFontToTexture(text, fontName, fontSize, quality);
    texture->size = textureSize;
    texture->name = name;
    texture->position = position;
    texture->angle = angleRadians;
    texture->flipHorizontally = flipHorizontally;
    texture->flipVertically = flipVertically;
    
    return texture;
}