#include "core/builder/ElementBuilder.h"

using namespace bkengine;

ElementBuilder ElementBuilder::createBuilder()
{
    return ElementBuilder();
}

ElementBuilder &ElementBuilder::setName(const std::string &name)
{
    ElementBuilder::name = name;
    return *this;
}

ElementBuilder &ElementBuilder::setParentScene(const std::shared_ptr<Scene> &parentScene)
{
    ElementBuilder::parentScene = parentScene;
    return *this;
}

ElementBuilder &ElementBuilder::setRenderBox(const RelRect &renderBox)
{
    ElementBuilder::renderBox = renderBox;
    return *this;
}

ElementBuilder &ElementBuilder::setCollisionBox(const RelRect &collisionBox)
{
    ElementBuilder::collisionBox = collisionBox;
    return *this;
}

ElementBuilder &ElementBuilder::setCollisionLayer(uint32_t collisionLayer)
{
    ElementBuilder::collisionLayer = collisionLayer;
    return *this;
}