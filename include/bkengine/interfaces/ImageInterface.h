#ifndef BKENGINE_IMAGEINTERFACE_H
#define BKENGINE_IMAGEINTERFACE_H

#include <string>

#include "core/ImageTexture.h"


namespace bkengine
{
    class ImageInterface
    {
    public:
        virtual std::shared_ptr<ImageTexture> renderImageFileToTexture(const std::string &filePath,
                                                                       const AbsRect &) = 0;
    };
}

#endif