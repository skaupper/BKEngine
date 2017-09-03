#ifndef BKENGINE_SCENE_H
#define BKENGINE_SCENE_H

#include <algorithm>
#include <cassert>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "core/ActivatableObject.h"
#include "core/Element.h"
#include "core/HierarchicalObject.h"
#include "interfaces/GraphicsInterface.h"
#include "utils/Event.h"
#include "utils/Logger.h"


namespace bkengine
{
    class Game;

    class Scene : public ActivatableObject, public HierarchicalObject<Element, Scene>
    {
        friend class Game;
        friend class GameUtils;
        friend class SceneBuilder;
        friend class SceneUtils;

    public:
        virtual ~Scene() = default;

        virtual bool onLoop();
        virtual bool onRender();
        virtual bool onEvent(const Event &);

    protected:
        explicit Scene() = default;

    private:
        void _onLoop();
        void _onRender();
        void _onEvent(const Event &);

        std::map<uint32_t, std::vector<std::shared_ptr<Element>>> collisionLayers;
    };
}

#endif
