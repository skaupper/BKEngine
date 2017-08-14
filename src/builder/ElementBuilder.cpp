#include "builder/ElementBuilder.h"

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

ElementBuilder &ElementBuilder::setParentScene(std::shared_ptr<Scene> parentScene)
{
    ElementBuilder::parentScene = parentScene;
    return *this;
}

ElementBuilder &ElementBuilder::setRenderBox(Rect renderBox)
{
    ElementBuilder::renderBox = renderBox;
    return *this;
}

ElementBuilder &ElementBuilder::setCollisionBox(Rect collisionBox)
{
    ElementBuilder::collisionBox = collisionBox;
    return *this;
}

ElementBuilder &ElementBuilder::setCollisionLayer(uint32_t collisionLayer)
{
    ElementBuilder::collisionLayer = collisionLayer;
    return *this;
}