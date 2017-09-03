#ifndef BKENGINE_SDLIMAGETEXTURE_H
#define BKENGINE_SDLIMAGETEXTURE_H

#include <SDL_surface.h>
#include <SDL_system.h>

#include "core/ImageTexture.h"
#include "exceptions/NotImplementedException.h"

namespace bkengine
{
    class SDLImageTexture : public ImageTexture
    {
        friend class SDLImageInterface;

    public:
        void onRender() override;

        const SDL_Texture *getTexture() const;

        ~SDLImageTexture();
        SDLImageTexture(SDL_Texture *);

    private:
        SDL_Texture *texture;
    };
}

#endif //BKENGINE_SDLIMAGETEXTURE_H
