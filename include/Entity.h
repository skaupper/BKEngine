#ifndef ENTITY_H
#define ENTITY_H

#include <memory>

#include "Element.h"
#include "Scene.h"

namespace bkengine
{
    class Entity : public Element
    {
        public:
            explicit Entity(const std::string &descr = "", const Location &loc = {0, 0}, bool isCollidable = false);
            virtual ~Entity();

            void move(float x, float y);
            void moveTo(float x, float y);
            virtual bool collidesWith(const Element &other) const;
    };
}

#endif
