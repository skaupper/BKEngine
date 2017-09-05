#ifndef BKENGINE_LAZY_TEXTURE_CONTAINER_H
#define BKENGINE_LAZY_TEXTURE_CONTAINER_H

#include <memory>

#include "core/ActivatableObject.h"
#include "core/Texture.h"
#include "utils/InterfaceContainer.h"


namespace bkengine
{
    class LazyTextureContainer : public ActivatableObject, public NameableObject
    {
        friend class Texture;

    public:
        explicit LazyTextureContainer(std::unique_ptr<Texture> texture);

        void load(const std::shared_ptr<InterfaceContainer> &);
        void unload();

        bool isLoaded();

        void onRender();

    protected:
        void *data = nullptr;
        
    private:
        std::unique_ptr<Texture> texture = nullptr;
        std::weak_ptr<GraphicsInterface> graphicsInterface;
        std::weak_ptr<ImageInterface> imageInterface;
    };
}

#endif  // BKENGINE_LAZY_TEXTURE_CONTAINER_H