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
            explicit Entity(Scene *parentScene, const std::string &descr = "",
                            const Rect &renderBox = Rect(),
                            int collisionLayer = -1);
            virtual ~Entity();

            void move(float x, float y);
            void moveTo(float x, float y);
            bool collidesWith();
            virtual bool collidesWith(const Element &other) const;

        private:
            constexpr static float MINIMUM_MOVE = 0.001;
            constexpr static float MAXIMUM_MOVE = 1.00;

            void moveSlowly(float x, float y);
            float bringClose(float value, float &location);
    };
}

#endif
