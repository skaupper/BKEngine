#ifndef BKENGINE_SCENE_BUILDER_H
#define BKENGINE_SCENE_BUILDER_H

#include <memory>
#include <string>

#include "core/Game.h"
#include "core/Scene.h"
#include "core/utils/GameUtils.h"
#include "exceptions/BuilderException.h"

namespace bkengine
{
    class Game;
    class Scene;

    class SceneBuilder
    {
    public:
        static SceneBuilder createBuilder();
        SceneBuilder &setName(const std::string &);
        SceneBuilder &setParentGame(const std::shared_ptr<Game> &);

        template <typename T>
        std::shared_ptr<T> build() const;


        template <typename T>
        static std::shared_ptr<T> createScene(const std::string &, const std::shared_ptr<Game> &);

    private:
        SceneBuilder() = default;

        std::string name;
        std::shared_ptr<Game> parentGame = nullptr;
    };
}

#include "templates/SceneBuilder_templates.h"

#endif  // BKENGINE_SCENE_BUILDER_H