#ifndef BKENGINE_SCENE_UTILS_H
#define BKENGINE_SCENE_UTILS_H

#include <memory>

#include "core/Scene.h"
#include "core/Element.h"
#include "exceptions/NameNotFoundException.h"


namespace bkengine
{
    class Scene;
    class Element;

    class SceneUtils
    {
    public:
        static void addElement(std::shared_ptr<Scene>, std::shared_ptr<Element>, uint32_t);
        static bool hasElement(std::shared_ptr<Scene>, const std::string &);
        static std::shared_ptr<Element> removeElement(std::shared_ptr<Scene>, const std::string &);
        static void moveElementToCollisionLayer(std::shared_ptr<Scene>, const std::string &, uint32_t);

    private:
        SceneUtils() = delete;
    };
}

#endif // BKENGINE_SCENE_UTILS_H