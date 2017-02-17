#ifndef ENTITY_H
#define ENTITY_H

#include <memory>

#include "Element.h"
#include "Scene.h"

namespace bkengine
{
    class Scene;

    class Entity : public Element
    {
        public:
            Entity(const Location &loc, std::shared_ptr<Scene> parentScene,
                   const std::string &descr = "", bool isCollidable = false);
            virtual ~Entity();

            void move(float x, float y);
            void moveTo(float x, float y);
            bool collidesWith(const Element &other);

            std::shared_ptr<Scene> parentScene;
    };
}

#endif // ENTITY_H
