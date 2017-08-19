#ifndef BKENGINE_ELEMENT_UTILS_H
#define BKENGINE_ELEMENT_UTILS_H

#include <algorithm>
#include <memory>

#include "core/Animation.h"
#include "core/Element.h"
#include "exceptions/NameAlreadyExistsException.h"
#include "exceptions/NameNotFoundException.h"


namespace bkengine
{
    class Animation;
    class Element;

    class ElementUtils
    {
    public:
        static void addAnimation(const std::shared_ptr<Element> &element, const std::shared_ptr<Animation> &animation);
        static bool hasAnimation(const std::shared_ptr<Element> &element, const std::string &name);
        static std::shared_ptr<Animation> removeAnimation(const std::shared_ptr<Element> &element,
                                                          const std::string &name);
        static std::vector<std::shared_ptr<Animation>> removeAllAnimations(const std::shared_ptr<Element> &element);

        static std::shared_ptr<Animation> getAnimation(const std::shared_ptr<Element> &element,
                                                       const std::string &name);
        static std::vector<std::string> getAnimationNames(const std::shared_ptr<Element> &element);
        static uint32_t getAnimationCount(const std::shared_ptr<Element> &element);

        static void activateAnimation(const std::shared_ptr<Element> &element, const std::string &name);
        static std::shared_ptr<Animation> getCurrentAnimation(const std::shared_ptr<Element> &element);

    private:
        ElementUtils() = delete;
    };
}

#endif  // BKENGINE_ELEMENT_UTILS_H