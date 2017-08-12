#include "builder/ImageTextureBuilder.h"

using namespace bkengine;


ImageTextureBuilder &ImageTextureBuilder::setGame(std::shared_ptr<Game> game)
{
    ImageTextureBuilder::game = game;
    return *this;
}

ImageTextureBuilder &ImageTextureBuilder::setFilePath(const std::string &filePath)
{
    ImageTextureBuilder::filePath = filePath;
    return *this;
}

ImageTextureBuilder &ImageTextureBuilder::setClip(Rect clip)
{
    clipRect = clip;
    return *this;
}

ImageTextureBuilder &ImageTextureBuilder::setTextureSize(Rect size)
{
    textureSize = size;
    return *this;
}