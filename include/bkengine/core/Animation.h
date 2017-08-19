#ifndef BKENGINE_ANIMATION_H
#define BKENGINE_ANIMATION_H

#include <cassert>
#include <memory>
#include <string>
#include <vector>

#include "core/Texture.h"


namespace bkengine
{
    class Animation
    {
        friend class Element;
        friend class ElementUtils;
        friend class AnimationBuilder;
        friend class AnimationUtils;

    public:
        virtual ~Animation() = default;

        virtual bool onRender();

        std::string getName() const;
        uint32_t getFramesPerTexture() const;

    protected:
        explicit Animation() = default;

        std::string name;

        uint32_t framesPerTexture;
        uint32_t frameCounter = 0;

    private:
        void _onRender();

        uint32_t currentTextureIndex = 0;
        std::vector<std::shared_ptr<Texture>> textures;
    };
}

#endif
