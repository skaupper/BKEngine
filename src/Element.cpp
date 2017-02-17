#include "Element.h"

using namespace bkengine;


Element::Element(const std::string &description, const Location &loc,
                 bool isCollidable) :
    description(description),
    location(loc),
    flipped(false),
    frame(0),
    isCollidable(isCollidable),
    currentAnimation(-1)
{
}

Location Element::getLocation()
{
    return Element::location;
}

void Element::setAnimation(unsigned int index)
{
    if (index >= animations.size()) {
        currentAnimation = 0;
    } else {
        currentAnimation = index;
    }
}

void Element::onRender()
{
    if (hasAnimation(currentAnimation)) {
        frame++;
        Animation &animation = getCurrentAnimation<Animation>();

        if (animation.hasTexture(0)) {
            animation.getNextTexture().onRender(location, flipped);
        }
    }
}

void Element::onLoop()
{
}

int Element::onEvent(SDL_Event *e)
{
    return 0;
}

bool Element::hasAnimation(unsigned int index)
{
    return index < animations.size();
}

bool Element::hasAnimation(const std::string &name)
{
    for (auto &animation : animations) {
        if (animation->getDescription() == name) {
            return true;
        }
    }

    return false;
}


void Element::removeAnimation(const std::string &name)
{
    int index = 0;

    for (auto &animation : animations) {
        if (animation->getDescription() == name) {
            animations.erase(animations.begin() + index);
            return;
        }

        index++;
    }

    Logger::LogCritical("Element::removeAnimation(const std::string &=" + name +
                        "): Animation not found");
    throw "Animation not found";
}

void Element::removeAnimation(unsigned int index)
{
    if (index < animations.size()) {
        animations.erase(animations.begin() + index);
    } else {
        Logger::LogCritical("Element::removeAnimation(int=" + std::to_string(
                                index) + "): Animation not found");
        throw "Animation not found";
    }
}

Element::~Element()
{
    animations.clear();
}

std::string Element::getDescription()
{
    return description;
}
