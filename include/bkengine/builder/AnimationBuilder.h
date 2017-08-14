#ifndef BKENGINE_ANIMATION_BUILDER_H
#define BKENGINE_ANIMATION_BUILDER_H

#include <memory>
#include <string>

#include "core/Animation.h"
#include "core/Element.h"


namespace bkengine
{
    class Element;
    class Animation;

    class AnimationBuilder
    {
    public:
        static AnimationBuilder createBuilder();
        AnimationBuilder &setName(const std::string &);
        AnimationBuilder &setFramesPerTexture(uint32_t);

        template <typename T>
        std::shared_ptr<T> build() const;

    private:
        AnimationBuilder() = default;

        std::string name;
        uint32_t framesPerTexture = 60;
    };
}

#include "templates/AnimationBuilder_templates.h"

#endif  // BKENGINE_ANIMATION_BUILDER_H