#include "core/impl/SDLImageTexture.h"

using namespace bkengine;

void SDLImageTexture::onRender()
{
    throw NotImplementedException();
}

const SDL_Texture *SDLImageTexture::getTexture() const
{
    return texture;
}

SDLImageTexture::~SDLImageTexture()
{
    SDL_DestroyTexture(texture);
}

SDLImageTexture::SDLImageTexture(SDL_Texture *texture)
{
    this->texture = texture;
}
