#ifndef BKENGINE_ENTITY_H
#define BKENGINE_ENTITY_H

#include <memory>

#include "core/Element.h"


namespace bkengine
{
    class Entity : public Element
    {
    public:
        virtual ~Entity() = default;

        void move(double x, double y);
        void moveTo(double x, double y);
        bool collidesWith();
        virtual bool collidesWith(const Element &other) const;


    protected:
        explicit Entity() = default;

        constexpr static double MINIMUM_MOVE = 0.001;
        constexpr static double MAXIMUM_MOVE = 1.00;

        void moveSlowly(double x, double y);
        double bringClose(double value, double &location);
    };
}

#endif
