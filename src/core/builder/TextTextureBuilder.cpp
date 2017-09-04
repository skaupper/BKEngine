#include "core/builder/TextTextureBuilder.h"

using namespace bkengine;


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


std::unique_ptr<Texture> TextTextureBuilder::build() const
{
    if (fontName.empty()) {
        throw BuilderException("Empty font names are not allowed!");
    }

    if (text.empty()) {
        throw BuilderException("An empty text cannot be rendered!");
    }

    if (fontSize < std::numeric_limits<double>::epsilon()) {
        throw BuilderException("The font size has to be set to a value greater than 0!");
    }

    std::unique_ptr<TextTexture> texture(new TextTexture());
    texture->fontName = fontName;
    texture->text = text;
    texture->fontSize = fontSize;
    texture->quality = quality;
    
    return std::move(texture);
}