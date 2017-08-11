#include "core/Element.h"

#include "core/Scene.h"
#include "serialization/GameSerializer.h"

using namespace bkengine;


Element::Element(Scene *parentScene, const std::string &name,
                 const Rect &renderBox,
                 int collisionLayer) :
    currentAnimation(-1),
    parentScene(parentScene),
    name(name),
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
        if (animation->getName() == name) {
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
        if (animation->getName() == name) {
            return true;
        }
    }

    return false;
}


void Element::removeAnimation(const std::string &name)
{
    int index = 0;

    for (auto &animation : animations) {
        if (animation->getName() == name) {
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

void Element::onRender(std::shared_ptr<GraphicsInterface> graphicsInterface,
                       const Rect &parentRect)
{
    if (hasAnimation(currentAnimation)) {
        Animation &animation = getCurrentAnimation<Animation>();

        if (animation.hasTexture(0)) {
            // TODO: flip is hardcoded!
            animation.getNextTexture().onRender(graphicsInterface,
                                                RelativeCoordinates::apply(renderBox, parentRect), false);
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

std::string Element::getName() const
{
    return name;
}

unsigned int Element::getAnimationCount() const
{
    return animations.size();
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
    Json::FastWriter writer;
    Serializable::deserialize(obj);

    if (!obj.isMember("animations") || !obj["animations"].isArray()) {
        Logger::LogCritical("Element::deserialize(const Json::Value &=<optimized out>): JSON object must have an member \"animations\" of type array. Deserialization aborted");
        return;
    }

    for (auto &animation : obj["animations"]) {
        auto a = GameSerializer::deserialize<Animation>(animation);
        a->setupEnvironment();
        addAnimation(a);
    }

    if (!obj.isMember("name")) {
        Logger::LogWarning("Element::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"name\"");
    } else {
        name = obj["name"].asString();
    }

    if (!obj.isMember("active")) {
        Logger::LogWarning("Element::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"active\"");
    } else {
        auto jsonActive = obj["active"];

        if (jsonActive.isInt()) {
            activate(jsonActive.asInt());
        } else {
            activate(jsonActive.asString());
        }
    }

    if (!obj.isMember("render_box")) {
        Logger::LogWarning("Element::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"render_box\"");
    } else {
        auto jsonRender = obj["render_box"];

        if (!jsonRender.isMember("x") || !jsonRender.isMember("y")
                || !jsonRender.isMember("w") || !jsonRender.isMember("h")) {
            Logger::LogCritical("Element::deserialize(const Json::Value &=<optimized out>): Member \"render_box\" must have the members \"x\", \"y\", \"w\" and \"h\". Deserialization aborted");
            clear();
            return;
        }

        if (!jsonRender["x"].isNumeric() || !jsonRender["y"].isNumeric()
                || !jsonRender["w"].isNumeric() || !jsonRender["h"].isNumeric()) {
            Logger::LogCritical("Element::deserialize(const Json::Value &=<optimized out>): Members \"x\", \"y\", \"w\" and \"h\" must be (floating point) numbers. Deserialization aborted");
            clear();
            return;
        }

        renderBox = {
            jsonRender["x"].asFloat(),
            jsonRender["y"].asFloat(),
            jsonRender["w"].asFloat(),
            jsonRender["h"].asFloat()
        };
    }

    if (!obj.isMember("collision_box")) {
        Logger::LogWarning("Element::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"collision_box\"");
    } else {
        auto jsonCollision = obj["collision_box"];

        if (!jsonCollision.isMember("x") || !jsonCollision.isMember("y")
                || !jsonCollision.isMember("w") || !jsonCollision.isMember("h")) {
            Logger::LogCritical("Element::deserialize(const Json::Value &=<optimized out>): Member \"collision_box\" must have the members \"x\", \"y\", \"w\" and \"h\". Deserialization aborted");
            clear();
            return;
        }

        if (!jsonCollision["x"].isNumeric() || !jsonCollision["y"].isNumeric()
                || !jsonCollision["w"].isNumeric() || !jsonCollision["h"].isNumeric()) {
            Logger::LogCritical("Element::deserialize(const Json::Value &=<optimized out>): Members \"x\", \"y\", \"w\" and \"h\" must be (floating point) numbers. Deserialization aborted");
            clear();
            return;
        }

        collisionBox = {
            jsonCollision["x"].asFloat(),
            jsonCollision["y"].asFloat(),
            jsonCollision["w"].asFloat(),
            jsonCollision["h"].asFloat()
        };
    }

    if (!obj.isMember("collision_layer")) {
        Logger::LogWarning("Element::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"collision_layer\"");
    } else {
        if (!obj["collision_layer"].isInt()) {
            Logger::LogWarning("Element::deserialize(const Json::Value &=<optimized out>): Member \"collision_layer\" must be a integer");
        } else {
            collisionLayer = obj["collision_layer"].asInt();
        }
    }
}

Json::Value Element::serialize() const
{
    Json::Value json;
    json["type"] = "ELEMENT";
    json["name"] = name;
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

    json["active"] = currentAnimation;
    return json;
}
