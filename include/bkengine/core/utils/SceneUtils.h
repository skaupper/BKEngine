#ifndef BKENGINE_SCENE_UTILS_H
#define BKENGINE_SCENE_UTILS_H

#include <memory>

#include "core/Element.h"
#include "core/Scene.h"
#include "exceptions/NameAlreadyExistsException.h"
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
        static std::vector<std::shared_ptr<Element>> removeAllElements(std::shared_ptr<Scene>);

        static std::shared_ptr<Element> getElement(std::shared_ptr<Scene>, const std::string &);
        static std::vector<std::string> getElementNames(std::shared_ptr<Scene>);
        static uint32_t getElementCount(std::shared_ptr<Scene>);

        static std::vector<std::shared_ptr<Element>> getCollisionLayer(std::shared_ptr<Scene>, uint32_t);
        static std::vector<std::shared_ptr<Element>> getCollisionLayerOfElement(std::shared_ptr<Scene>,
                                                                                std::shared_ptr<Element>);

        static void moveElementToCollisionLayer(std::shared_ptr<Scene>, const std::string &, uint32_t);

    private:
        SceneUtils() = delete;
    };
}

#endif  // BKENGINE_SCENE_UTILS_H