#include "Entity.h"

using namespace bkengine;


Entity::~Entity()
{
}

void Entity::move(float x, float y)
{
    if (std::abs(x) < MINIMUM_MOVE && std::abs(y) < MINIMUM_MOVE) {
        return;
    }

    moveSlowly(x, y);
}

void Entity::moveTo(float x, float y)
{
    renderBox.x = x;
    renderBox.y = y;
}

bool Entity::collidesWith()
{
    for (auto element : getCollisionLayer()) {
        if (element == this) {
            continue;
        }

        if (collidesWith(*element)) {
            return true;
        }
    }

    return false;
}

bool Entity::collidesWith(const Element &other) const
{
    Rect collisionRect = getCollisionBox();
    Rect otherCollisionRect = other.getCollisionBox();
    float x = collisionRect.x;
    float y = collisionRect.y;
    float h = collisionRect.h;
    float w = collisionRect.w;
    float otherx = otherCollisionRect.x;
    float othery = otherCollisionRect.y;
    float otherh = otherCollisionRect.h;
    float otherw = otherCollisionRect.w;

    if (x < otherx + otherw &&
            x + w > otherx &&
            y < othery + otherh &&
            h + y > othery) {
        Logger::LogDebug("collision");
        return true;
    }

    return false;
}

void Entity::moveSlowly(float x, float y)
{
    bool finishedX = false, finishedY = false;

    while (!finishedX || !finishedY) {
        float moveX = x, moveY = y;

        if (std::abs(x) > MAXIMUM_MOVE) {
            moveX = MAXIMUM_MOVE * sgn(x);
        }

        if (std::abs(y) > MAXIMUM_MOVE) {
            moveY = MAXIMUM_MOVE * sgn(y);
        }

        float moved = bringClose(moveX, renderBox.x);
        x -= moved;
        finishedX = std::abs(moved) < MINIMUM_MOVE;
        moved = bringClose(moveY, renderBox.y);
        y -= moved;
        finishedY = std::abs(moved) < MINIMUM_MOVE;
    }
}

float Entity::bringClose(float value, float &location)
{
    float originalLocation = location;
    bool collision = false;

    while (std::abs(value) > MINIMUM_MOVE && !collision) {
        float tmpValue = value;

        if (std::abs(tmpValue) > MAXIMUM_MOVE) {
            tmpValue = MAXIMUM_MOVE * sgn(value);
        }

        value -= tmpValue;

        while (std::abs(tmpValue) > MINIMUM_MOVE) {
            location += tmpValue;

            if (collidesWith()) {
                collision = true;
                location -= tmpValue;
            }

            if (collision) {
                tmpValue /= 2;
            } else {
                tmpValue = 0;
            }
        }
    }

    return location - originalLocation;
}
