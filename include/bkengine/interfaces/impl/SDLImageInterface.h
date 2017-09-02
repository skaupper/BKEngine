#ifndef BKENGINE_SDLIMAGEINTERFACE_H
#define BKENGINE_SDLIMAGEINTERFACE_H

#include <SDL_image.h>
#include <SDL_system.h>
#include <fstream>

#include "interfaces/ImageInterface.h"

namespace bkengine
{
    class SDLImageInterface : public ImageInterface
    {
    public:
        virtual void init();
        virtual void cleanup();
        virtual std::shared_ptr<ImageTexture> renderImageFileToTexture(const std::string &filePath,
                                                                       const AbsRect &) override;
    };
}

#endif //BKENGINE_SDLIMAGEINTERFACE_H
