#include "Entity.h"

using namespace bkengine;


Entity::Entity(const std::string &descr, const Rect &renderBox,
               bool isCollidable) :
    Element(descr, renderBox, isCollidable)
{
}

Entity::~Entity()
{
}

void Entity::move(float x, float y)
{
    renderBox.x += x;
    renderBox.y += y;
}


void Entity::moveTo(float x, float y)
{
    renderBox.x = x;
    renderBox.y = y;
}

bool Entity::collidesWith(const Element &other) const
{
    float x = renderBox.x;
    float y = renderBox.y;
    float h = renderBox.h;
    float w = renderBox.w;
    float otherx = other.getRenderBox().x;
    float othery = other.getRenderBox().y;
    float otherh = other.getRenderBox().h;
    float otherw = other.getRenderBox().w;

    if (x < otherx + otherw &&
        x + w > otherx &&
        y < othery + otherh &&
        h + y > othery) {
        return true;
    }

    return false;
}
