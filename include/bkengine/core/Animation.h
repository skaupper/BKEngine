#ifndef BKENGINE_ANIMATION_H
#define BKENGINE_ANIMATION_H

#include <cassert>
#include <memory>
#include <string>
#include <vector>

#include "core/Texture.h"


namespace bkengine
{
    class Animation : public ActivatorObject<LazyTextureContainer, Animation>
    {
        friend class Element;
        friend class ElementUtils;
        friend class AnimationBuilder;
        friend class AnimationUtils;

    public:
        virtual ~Animation() = default;

        virtual bool onRender();

        uint32_t getFramesPerTexture() const;

    protected:
        explicit Animation() = default;

        uint32_t framesPerTexture;
        uint32_t frameCounter = 0;

    private:
        void _onRender();
    };
}

#endif
