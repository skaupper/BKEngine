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

void Element::setName(const std::string &name)
{
    Element::name = name;
}

RelRect Element::getRenderBox() const
{
    return renderBox;
}

void Element::setRenderBox(const RelRect &renderBox)
{
    Element::renderBox = renderBox;
}

RelRect Element::getCollisionBox() const
{
    return collisionBox;
}

void Element::setCollisionBox(const RelRect &collisionBox)
{
    Element::collisionBox = collisionBox;
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
