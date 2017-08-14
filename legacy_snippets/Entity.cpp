#include "core/Entity.h"

using namespace bkengine;


template <typename T>
static int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

void Entity::move(double x, double y)
{
    if (std::abs(x) < MINIMUM_MOVE && std::abs(y) < MINIMUM_MOVE) {
        return;
    }

    moveSlowly(x, y);
}

void Entity::moveTo(double x, double y)
{
    renderBox.x = x;
    renderBox.y = y;
}

bool Entity::collidesWithSomeThingOnSameCollisionLayer()
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
    double x = collisionRect.x;
    double y = collisionRect.y;
    double h = collisionRect.h;
    double w = collisionRect.w;
    double otherx = otherCollisionRect.x;
    double othery = otherCollisionRect.y;
    double otherh = otherCollisionRect.h;
    double otherw = otherCollisionRect.w;

    if (x < otherx + otherw && x + w > otherx && y < othery + otherh && h + y > othery) {
        Logger::debug << "Entity::collidesWith(std::shared_ptr<Element>): collision";
        return true;
    }

    return false;
}

void Entity::moveSlowly(double x, double y)
{
    bool finishedX = false, finishedY = false;

    while (!finishedX || !finishedY) {
        double moveX = x, moveY = y;

        if (std::abs(x) > MAXIMUM_MOVE) {
            moveX = MAXIMUM_MOVE * sgn(x);
        }

        if (std::abs(y) > MAXIMUM_MOVE) {
            moveY = MAXIMUM_MOVE * sgn(y);
        }

        double moved = bringClose(moveX, renderBox.x);
        x -= moved;
        finishedX = std::abs(moved) < MINIMUM_MOVE;
        moved = bringClose(moveY, renderBox.y);
        y -= moved;
        finishedY = std::abs(moved) < MINIMUM_MOVE;
    }
}

double Entity::bringClose(double value, double &location)
{
    double originalLocation = location;
    bool collision = false;

    while (std::abs(value) > MINIMUM_MOVE && !collision) {
        double tmpValue = value;

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
