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
    class Animation;

    class Element
    {
        friend class Scene;
        friend class SceneUtils;

    public:
        virtual ~Element() = default;

        virtual bool onRender();
        virtual bool onLoop();
        virtual bool onEvent(const Event &);

    protected:
        explicit Element() = default;

        std::string name;

        Rect renderBox;
        Rect collisionBox;

    private:
        void _onRender();
        void _onLoop();
        void _onEvent(const Event &);

        std::weak_ptr<Scene> parentScene;

        uint32_t collisionLayer = 0;

        std::shared_ptr<Animation> currentAnimation;
        std::vector<std::shared_ptr<Animation>> animations;
    };
}

#endif
