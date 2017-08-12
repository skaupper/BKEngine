#ifndef BKENGINE_IMAGEINTERFACE_H
#define BKENGINE_IMAGEINTERFACE_H

#include <string>

#include "utils/ImageTexture.h"


namespace bkengine
{
    class ImageInterface
    {
    public:
        virtual std::shared_ptr<ImageTexture> renderImageFileToTexture(const std::string &filePath) = 0;
    };
}

#endif