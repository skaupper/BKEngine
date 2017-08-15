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
        static void addElement(const std::shared_ptr<Scene> &, const std::shared_ptr<Element> &, uint32_t);
        static bool hasElement(const std::shared_ptr<Scene> &, const std::string &);
        static std::shared_ptr<Element> removeElement(const std::shared_ptr<Scene> &, const std::string &);
        static std::vector<std::shared_ptr<Element>> removeAllElements(const std::shared_ptr<Scene> &);

        static std::shared_ptr<Element> getElement(const std::shared_ptr<Scene> &, const std::string &);
        static std::vector<std::string> getElementNames(const std::shared_ptr<Scene> &);
        static uint32_t getElementCount(const std::shared_ptr<Scene> &);

        static std::vector<std::shared_ptr<Element>> getCollisionLayer(const std::shared_ptr<Scene> &, uint32_t);
        static std::vector<std::shared_ptr<Element>> getCollisionLayerOfElement(const std::shared_ptr<Scene> &,
                                                                                const std::shared_ptr<Element> &);

        static void moveElementToCollisionLayer(const std::shared_ptr<Scene> &, const std::string &, uint32_t);

    private:
        SceneUtils() = delete;
    };
}

#endif  // BKENGINE_SCENE_UTILS_H