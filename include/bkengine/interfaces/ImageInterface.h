#ifndef BKENGINE_IMAGEINTERFACE_H
#define BKENGINE_IMAGEINTERFACE_H

#include <string>

#include "utils/Image.h"


namespace bkengine
{
    class ImageInterface
    {
        public:
            virtual std::shared_ptr<Image> loadImageFromFile(const std::string &filePath) = 0;
    };
}

#endif