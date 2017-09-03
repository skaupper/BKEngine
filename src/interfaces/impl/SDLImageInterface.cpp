#include "interfaces/impl/SDLImageInterface.h"
#include <core/builder/ImageTextureBuilder.h>
#include <core/impl/SDLImageTexture.h>

using namespace bkengine;

void SDLImageInterface::init()
{
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_PNG);
}

void SDLImageInterface::cleanup()
{
    IMG_Quit();
}

std::shared_ptr<ImageTexture> SDLImageInterface::renderImageFileToTexture(const std::string &filePath,
                                                                          const AbsRect &clip)
{
    std::string logPrefix = "SDLImageInterface::renderImageFileToTexture(const std::string &=" + filePath
                            + ", const AbsRect &=" + clip.toString() + "): ";

    SDL_Surface *raw_surface = IMG_Load(filePath.c_str());
    if (!raw_surface) {
        Logger::error << logPrefix << "Failed to load image: " << SDL_GetError();
        return nullptr;
    }

    //TODO: add renderer when GraphicsInterface is finished
    SDL_Texture *raw_texture = SDL_CreateTextureFromSurface(nullptr, raw_surface);
    SDL_FreeSurface(raw_surface);

    std::shared_ptr<SDLImageTexture> texture(new SDLImageTexture(raw_texture));
    texture->clip = clip;

    return std::static_pointer_cast<ImageTexture>(texture);
}