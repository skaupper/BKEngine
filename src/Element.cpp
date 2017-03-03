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
    collisionLayer(collisionLayer)
{
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

void Element::setupAnimations()
{
}

void Element::setupEnvironment()
{
}

void Element::onRender(const Rect &parentRect)
{
    if (hasAnimation(currentAnimation)) {
        Animation &animation = getCurrentAnimation<Animation>();

        if (animation.hasTexture(0)) {
            // TODO: flip is hardcoded!
            animation.getNextTexture().onRender(RelativeCoordinates::apply(renderBox,
                                                parentRect), false);
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

void Element::deserialize(const Json::Value &obj)
{
    Serializable::deserialize(obj);
    description = obj["description"].asString();
    renderBox = {
        obj["render_box"]["x"].asFloat(),
        obj["render_box"]["y"].asFloat(),
        obj["render_box"]["w"].asFloat(),
        obj["render_box"]["h"].asFloat()
    };
    collisionBox = {
        obj["collision_box"]["x"].asFloat(),
        obj["collision_box"]["y"].asFloat(),
        obj["collision_box"]["w"].asFloat(),
        obj["collision_box"]["h"].asFloat()
    };
    collisionLayer = obj["collision_layer"].asInt();

    for (auto &animation : obj["animations"]) {
        auto a = GameSerializer::deserialize<Animation>(animation);
        a->setupEnvironment();
        addAnimation(a);
    }
}

Json::Value Element::serialize() const
{
    Json::Value json;
    json["type"] = "ELEMENT";
    json["description"] = description;
    json["render_box"]["x"] = renderBox.x;
    json["render_box"]["y"] = renderBox.y;
    json["render_box"]["w"] = renderBox.w;
    json["render_box"]["h"] = renderBox.h;
    json["collision_box"]["x"] = collisionBox.x;
    json["collision_box"]["y"] = collisionBox.y;
    json["collision_box"]["w"] = collisionBox.w;
    json["collision_box"]["h"] = collisionBox.h;
    json["collision_layer"] = collisionLayer;

    json["animations"] = Json::arrayValue;

    for (auto animation : animations) {
        json["animations"].append(animation->serialize());
    }
    return json;
}
