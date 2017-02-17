#include "Entity.h"
#include <iostream>

using namespace bkengine;


Entity::Entity(const Location &loc, std::shared_ptr<Scene> parentScene,
               const std::string &descr, bool isCollidable) :
    Element(loc, descr, isCollidable), parentScene(parentScene)
{
}

void Entity::move(float x, float y)
{
    Entity::location->x += x;
    Entity::location->y += y;
}


void Entity::moveTo(float x, float y)
{
    Entity::location->x = x;
    Entity::location->y = y;
}

bool Entity::collidesWith(const Element &other)
{
    float x = location->x;
    float y = location->y;
    float h = collisionRect->h;
    float w = collisionRect->w;
    float otherx = other->location->x;
    float othery = other->location->y;
    float otherh = other->collisionRect->h;
    float otherw = other->collisionRect->w;
    bool collides = false;

    if ((x >= otherx && x <= otherx + otherw) && (y >= othery
            && y <= othery + otherh)) {
        collides = true;
    }

    if ((x + w >= otherx && x + w <= otherx + otherw) && (y >= othery
            && y <= othery + otherh)) {
        collides = true;
    }

    if ((x < otherx && x + w > otherx + otherw) && (y >= othery
            && y <= othery + otherh)) {
        collides = true;
    }

    if ((x >= otherx && x <= otherx + otherw) && (y + h >= othery
            && y + h <= othery + otherh)) {
        collides = true;
    }

    if ((x + w >= otherx && x + w <= otherx + otherw) && (y + h >= othery
            && y + h <= othery + otherh)) {
        collides = true;
    }

    if ((x < otherx && x + w > otherx + otherw) && (y + h >= othery
            && y + h <= othery + otherh)) {
        collides = true;
    }

    if ((x >= otherx && x <= otherx + otherw) && (y <= othery
            && y + h >= othery + otherh)) {
        collides = true;
    }

    if ((x + w >= otherx && x + w <= otherx + otherw) && (y <= othery
            && y + h >= othery + otherh)) {
        collides = true;
    }

    if ((x < otherx && x + w > otherx + otherw) && (y <= othery
            && y + h >= othery + otherh)) {
        collides = true;
    }

    // TODO: check if all cases are here!
    return collides;
}

Entity::~Entity()
{
}
