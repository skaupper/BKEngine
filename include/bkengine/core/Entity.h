#ifndef BKENGINE_ENTITY_H
#define BKENGINE_ENTITY_H

#include <memory>

#include "core/Element.h"
#include "core/Scene.h"


namespace bkengine
{
    class Entity : public Element
    {
        public:
            using Element::Element;
            virtual ~Entity();

            void move(float x, float y);
            void moveTo(float x, float y);
            bool collidesWith();
            virtual bool collidesWith(const Element &other) const;


        protected:
            constexpr static float MINIMUM_MOVE = 0.001;
            constexpr static float MAXIMUM_MOVE = 1.00;

            void moveSlowly(float x, float y);
            float bringClose(float value, float &location);
    };
}

#endif
