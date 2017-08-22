#include "core/Element.h"

using namespace bkengine;


bool Element::onRender()
{
    return false;
}

bool Element::onLoop()
{
    return false;
}

bool Element::onEvent(const Event &e)
{
    return false;
}


std::string Element::getName() const
{
    return name;
}

RelRect Element::getRenderBox() const
{
    return renderBox;
}

RelRect Element::getCollisionBox() const
{
    return collisionBox;
}


void Element::_onRender()
{
    bool suppress = onRender();
    if (suppress) {
        return;
    }

    if (currentAnimation != nullptr) {
        currentAnimation->_onRender();
    }
}

void Element::_onLoop()
{
    (void) onLoop();
}

void Element::_onEvent(const Event &event)
{
    (void) onEvent(event);
}
