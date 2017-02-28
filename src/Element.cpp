#include "Element.h"
#include "Scene.h"

using namespace bkengine;


Element::Element(Scene *parentScene, const std::string &description,
                 const Rect &renderBox,
                 int collisionLayer) :
    currentAnimation(-1),
    parentScene(parentScene),
    description(description),
    renderBox(renderBox),
    collisionBox(Rect()),
    frame(0),
    collisionLayer(collisionLayer),
    flipped(false)
{
    setup();
}

Element::~Element()
{
    clear();
}

void Element::activate(unsigned int index)
{
    if (index >= animations.size()) {
        Logger::LogWarning("Element::activate(unsigned int=" +
                           std::to_string(index) + "): Index out of bounds");
        currentAnimation = 0;
    } else {
        currentAnimation = index;
    }
}

void Element::activate(const std::string &name)
{
    int index = 0;

    for (auto &animation : animations) {
        if (animation->getDescription() == name) {
            activate(index);
            return;
        }

        index++;
    }

    Logger::LogWarning("Element::activate(const std::string=" + name +
                       "): Animation not found");
}

bool Element::hasAnimation(unsigned int index) const
{
    return index < animations.size();
}

bool Element::hasAnimation(const std::string &name) const
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

Animation &Element::getAnimation(const std::string &name)
{
    return getAnimation<Animation>(name);
}

Animation &Element::getAnimation(unsigned int index)
{
    return getAnimation<Animation>(index);
}

Animation &Element::getCurrentAnimation()
{
    return getCurrentAnimation<Animation>();
}

void Element::setup()
{
}

void Element::onRender(const Rect &parentRect)
{
    if (hasAnimation(currentAnimation)) {
        frame++;
        Animation &animation = getCurrentAnimation<Animation>();

        if (animation.hasTexture(0)) {
            animation.getNextTexture().onRender(RelativeCoordinates::apply(renderBox,
                                                parentRect), flipped);
        }
    }
}

void Element::onLoop()
{
}

bool Element::onEvent(const Event &e)
{
    return true;
}

void Element::applyCollisionBox(const Rect &rect)
{
    collisionBox = rect;
}

Rect Element::getCollisionBox() const
{
    return RelativeCoordinates::apply(collisionBox, renderBox);
}

void Element::setRenderBox(const Rect &rect)
{
    renderBox = rect;
}

Rect Element::getRenderBox() const
{
    return renderBox;
}

std::string Element::getDescription() const
{
    return description;
}

void Element::clear()
{
    animations.clear();
}

std::vector<Element *> Element::getCollisionLayer()
{
    return parentScene->getCollisionLayer(collisionLayer);
}
