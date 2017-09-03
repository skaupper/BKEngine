#ifndef BKENGINE_LAZY_TEXTURE_CONTAINER_H
#define BKENGINE_LAZY_TEXTURE_CONTAINER_H

#include <memory>

#include "core/Texture.h"
#include "utils/InterfaceContainer.h"


namespace
{
    class LazyTextureContainer
    {
    public:
        void load(const std::shared_ptr<InterfaceContainer> &);
        void unload();

        bool isLoaded();

        void onRender();

    private:
        Texture *texture = nullptr;
        std::weak_ptr<GraphicsInterface> graphicsInterface;
        std::weak_ptr<ImageInterface> imageInterface;
    };
}

#endif // BKENGINE_LAZY_TEXTURE_CONTAINER_H