#ifndef BKENGINE_ANIMATION_H
#define BKENGINE_ANIMATION_H

#include <cassert>
#include <memory>
#include <string>
#include <vector>

#include "core/Texture.h"


namespace bkengine
{
    class Texture;

    class Animation
    {
        friend class Element;
        friend class ElementUtils;
        friend class AnimationBuilder;

    public:
        virtual ~Animation() = default;

        virtual bool onRender();

    protected:
        explicit Animation() = default;


        std::string name;

        unsigned int framesPerTexture;
        unsigned int frameCounter = 0;

    private:
        void _onRender();

        uint32_t currentTextureIndex = 0;
        std::vector<std::shared_ptr<Texture>> textures;
    };
}

#endif
