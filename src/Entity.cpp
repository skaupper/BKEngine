#include "Entity.h"

using namespace bkengine;


Entity::Entity(Scene *parentScene, const std::string &descr, const Rect &renderBox,
               int collisionLayer) :
    Element(parentScene, descr, renderBox, collisionLayer)
{
}

Entity::~Entity()
{
}

void Entity::move(float x, float y)
{
    if (x < MINIMUM_MOVE && y < MINIMUM_MOVE) {
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
        if(element == this) {
            continue;
        }
        if(collidesWith(*element)) {
            return true;
        }
    }
    return false;
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

void Entity::moveSlowly(float x, float y)
{
    float moved = 0;
    float moveX, moveY;
    bool finishedX = false, finishedY = false;
    while(!finishedX || !finishedY) {
        moveX = x;
        if(std::abs(x) > MAXIMUM_MOVE) {
            moveX = MAXIMUM_MOVE * sgn(x);
        }
        moveY = y;
        if(std::abs(y) > MAXIMUM_MOVE) {
            moveY = MAXIMUM_MOVE * sgn(y);
        }
        moved = bringClose(moveX, renderBox.x);
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
    float collision = false;
    while(std::abs(value) > MINIMUM_MOVE && !collision) {
        float tmpValue = value;
        if(std::abs(tmpValue) > MAXIMUM_MOVE) {
            tmpValue = MAXIMUM_MOVE * sgn(value);
        }
        value -= tmpValue;

        while(std::abs(tmpValue) > MINIMUM_MOVE) {
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
