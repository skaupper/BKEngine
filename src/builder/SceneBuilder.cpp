#include "builder/SceneBuilder.h"

using namespace bkengine;


SceneBuilder SceneBuilder::createBuilder()
{
    return SceneBuilder();
}

SceneBuilder &SceneBuilder::setName(const std::string &name)
{
    SceneBuilder::name = name;
    return *this;
}

SceneBuilder &SceneBuilder::setParentGame(std::shared_ptr<Game> parentGame)
{
    SceneBuilder::parentGame = parentGame;
    return *this;
}