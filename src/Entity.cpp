#include "Entity.h"

using namespace bkengine;


Entity::Entity(const std::string &descr, const Location &loc,
               bool isCollidable) :
    Element(descr, loc, isCollidable)
{
}

Entity::~Entity()
{
}

void Entity::move(float x, float y)
{
    Entity::location.x += x;
    Entity::location.y += y;
}


void Entity::moveTo(float x, float y)
{
    Entity::location.x = x;
    Entity::location.y = y;
}

bool Entity::collidesWith(const Element &other) const
{
    float x = location.x;
    float y = location.y;
    float h = collisionRect.h;
    float w = collisionRect.w;
    float otherx = other.location.x;
    float othery = other.location.y;
    float otherh = other.collisionRect.h;
    float otherw = other.collisionRect.w;

    if (x < otherx + otherw &&
            x + w > otherx &&
            y < othery + otherh &&
            h + y > othery) {
        return true;
    }

    return false;
}
