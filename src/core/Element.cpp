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

    if (getActivatedObject()) {
        getActivatedObject()->_onRender();
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
