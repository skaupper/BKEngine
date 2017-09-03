#ifndef BKENGINE_ELEMENT_H
#define BKENGINE_ELEMENT_H

#include <memory>
#include <string>
#include <vector>

#include "core/Animation.h"
#include "utils/Event.h"
#include "utils/Geometry.h"


namespace bkengine
{
    class Scene;

    class Element : public ActivatorObject<Animation, Element>  //, public HierarchicalObject<Element, Element>
    {
        friend class Scene;
        friend class SceneUtils;
        friend class ElementBuilder;
        friend class ElementUtils;

    public:
        virtual ~Element() = default;

        virtual bool onRender();
        virtual bool onLoop();
        virtual bool onEvent(const Event &);

        RelRect getRenderBox() const;
        RelRect getCollisionBox() const;

    protected:
        explicit Element() = default;

        Rect renderBox;
        Rect collisionBox;

    private:
        void _onRender();
        void _onLoop();
        void _onEvent(const Event &);

        uint32_t collisionLayer = 0;
    };
}

#endif
