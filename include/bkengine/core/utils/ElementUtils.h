#ifndef BKENGINE_ELEMENT_UTILS_H
#define BKENGINE_ELEMENT_UTILS_H

#include <memory>

#include "core/Animation.h"
#include "core/Element.h"
#include "exceptions/NameNotFoundException.h"


namespace bkengine
{
    class Animation;
    class Element;

    class ElementUtils
    {
    public:
        static void addAnimation(std::shared_ptr<Element>, std::shared_ptr<Animation>);
        static bool hasAnimation(std::shared_ptr<Element>, const std::string &);
        static std::shared_ptr<Animation> removeAnimation(std::shared_ptr<Element>, const std::string &);
        static void activateAnimation(std::shared_ptr<Element>, const std::string &);

    private:
        ElementUtils() = delete;
    };
}

#endif  // BKENGINE_ELEMENT_UTILS_H