#include "core/builder/ImageTextureBuilder.h"

using namespace bkengine;


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


std::unique_ptr<Texture> ImageTextureBuilder::build() const
{
    if (filePath.empty()) {
        throw BuilderException("A file for the image has to be set!");
    }

    std::unique_ptr<ImageTexture> texture(new ImageTexture());
    texture->clipRect = clipRect;
    texture->filePath = filePath;
    
    return std::move(texture);
}