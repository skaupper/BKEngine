#ifndef BKENGINE_ANIMATION_UTILS_H
#define BKENGINE_ANIMATION_UTILS_H

#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

#include "core/Animation.h"
#include "exceptions/NameAlreadyExistsException.h"
#include "exceptions/NameNotFoundException.h"


namespace bkengine
{
    class Texture;
    class Animation;

    class AnimationUtils
    {
    public:
        static void addTexture(const std::shared_ptr<Animation> &animation, const std::shared_ptr<Texture> &texture);
        static bool hasTexture(const std::shared_ptr<Animation> &animation, const std::string &name);
        static std::shared_ptr<Texture> removeTexture(const std::shared_ptr<Animation> &animation,
                                                      const std::string &name);
        static std::vector<std::shared_ptr<Texture>> removeAllTextures(const std::shared_ptr<Animation> &animation);

        static std::shared_ptr<Texture> getTexture(const std::shared_ptr<Animation> &animation,
                                                   const std::string &name);
        static std::vector<std::string> getTextureNames(const std::shared_ptr<Animation> &animation);
        static uint32_t getTextureCount(const std::shared_ptr<Animation> &animation);

        static std::shared_ptr<Texture> getCurrentTexture(const std::shared_ptr<Animation> &animation);

    private:
        AnimationUtils() = delete;
    };
}

#endif  // BKENGINE_ANIMATION_UTILS_H