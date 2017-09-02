#include "core/builder/ImageTextureBuilder.h"

using namespace bkengine;

ImageTextureBuilder &ImageTextureBuilder::setGame(const std::shared_ptr<Game> &game)
{
    ImageTextureBuilder::game = game;
    return *this;
}

ImageTextureBuilder &ImageTextureBuilder::setName(const std::string &name)
{
    ImageTextureBuilder::name = name;
    return *this;
}

ImageTextureBuilder &ImageTextureBuilder::setFilePath(const std::string &filePath)
{
    ImageTextureBuilder::filePath = filePath;
    return *this;
}

ImageTextureBuilder &ImageTextureBuilder::setClip(const AbsRect &clip)
{
    clipRect = clip;
    return *this;
}

ImageTextureBuilder &ImageTextureBuilder::setTexturePosition(const Point &position)
{
    ImageTextureBuilder::position = position;
    return *this;
}

ImageTextureBuilder &ImageTextureBuilder::setTextureSize(const RelRect &size)
{
    textureSize = size;
    return *this;
}

ImageTextureBuilder &ImageTextureBuilder::setRotation(double angle)
{
    angleRadians = angle;
    return *this;
}

ImageTextureBuilder &ImageTextureBuilder::setFlip(bool horizontal, bool vertical)
{
    flipHorizontally = horizontal;
    flipVertically = vertical;
    return *this;
}

std::shared_ptr<Texture> ImageTextureBuilder::build() const
{
    if (game == nullptr) {
        throw BuilderException("You have to set the target game for the texture!");
    }

    if (name.empty()) {
        throw BuilderException("You have to specify a name for the texture!");
    }

    if (filePath.empty()) {
        throw BuilderException("A file for the image has to be set!");
    }

    auto imageInterface = game->interfaceContainer.getImageInterface();
    if (imageInterface == nullptr) {
        throw BuilderException("The given game has to have an image interface set!");
    }

    std::shared_ptr<Texture> texture = imageInterface->renderImageFileToTexture(filePath, clipRect);
    texture->size = textureSize;
    texture->name = name;
    texture->position = position;
    texture->angle = angleRadians;
    texture->flipHorizontally = flipHorizontally;
    texture->flipVertically = flipVertically;

    return texture;
}