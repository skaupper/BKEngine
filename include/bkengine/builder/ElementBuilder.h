#ifndef BKENGINE_ELEMENT_BUILDER_H
#define BKENGINE_ELEMENT_BUILDER_H

#include <memory>
#include <string>

#include "core/Element.h"
#include "core/Scene.h"
#include "core/utils/SceneUtils.h"
#include "exceptions/BuilderException.h"
#include "utils/Geometry.h"


namespace bkengine
{
    class Scene;
    class Element;

    class ElementBuilder
    {
    public:
        static ElementBuilder createBuilder();
        ElementBuilder &setName(const std::string &);
        ElementBuilder &setParentScene(const std::shared_ptr<Scene> &);
        ElementBuilder &setRenderBox(const Rect &);
        ElementBuilder &setCollisionBox(const Rect &);
        ElementBuilder &setCollisionLayer(uint32_t);

        template <typename T>
        std::shared_ptr<T> build() const;

    private:
        ElementBuilder() = default;

        std::string name;
        std::shared_ptr<Scene> parentScene = nullptr;
        Rect renderBox = {0, 0, 100, 100};
        Rect collisionBox = {0, 0, 100, 100};
        uint32_t collisionLayer = 0;
    };
}

#include "templates/ElementBuilder_templates.h"

#endif  // BKENGINE_ELEMENT_BUILDER_H