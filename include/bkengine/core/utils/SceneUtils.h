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
        static void addElement(const std::shared_ptr<Scene> &scene,
                               const std::shared_ptr<Element> &element,
                               uint32_t collisionLayerIndex);
        static bool hasElement(const std::shared_ptr<Scene> &scene, const std::string &name);
        static std::shared_ptr<Element> removeElement(const std::shared_ptr<Scene> &scene, const std::string &name);
        static std::vector<std::shared_ptr<Element>> removeAllElements(const std::shared_ptr<Scene> &scene);

        static std::shared_ptr<Element> getElement(const std::shared_ptr<Scene> &scene, const std::string &name);
        static std::vector<std::string> getElementNames(const std::shared_ptr<Scene> &scene);
        static uint32_t getElementCount(const std::shared_ptr<Scene> &scene);

        static std::vector<std::shared_ptr<Element>> getCollisionLayer(const std::shared_ptr<Scene> &scene,
                                                                       uint32_t collisionLayerIndex);
        static std::vector<std::shared_ptr<Element>>
        getCollisionLayerOfElement(const std::shared_ptr<Scene> &scene, const std::shared_ptr<Element> &element);

        static void moveElementToCollisionLayer(const std::shared_ptr<Scene> &scene,
                                                const std::string &name,
                                                uint32_t collisionLayerIndex);

    private:
        SceneUtils() = delete;
    };
}

#endif  // BKENGINE_SCENE_UTILS_H