#include "Animation.h"

using namespace bkengine;

Animation::Animation(const std::string &name,
                     unsigned int framesPerTexture) :
    currentTexture(0),
    name(name),
    frameCounter(0),
    framesPerTexture(framesPerTexture)
{
}

void Animation::reset()
{
    frameCounter = 0;
    currentTexture = -1;
}

Texture &Animation::getNextTexture()
{
    auto &tmp = getCurrentTexture();
    incFrameCount();
    return tmp;
}

Texture &Animation::getCurrentTexture()
{
    if (hasTexture(currentTexture)) {
        return *textures.at(currentTexture);
    }

    Logger::LogCritical("Animation::getCurrentTexture(): Texture not found");
    throw "Texture not found";
}

bool Animation::hasTexture(unsigned int index) const
{
    return index < textures.size();
}

void Animation::incFrameCount()
{
    if (framesPerTexture == 0) {
        return;
    }

    if (frameCounter < framesPerTexture - 1) {
        frameCounter++;
    } else {
        frameCounter = 0;
        currentTexture = (currentTexture + 1) % textures.size();
    }
}

void Animation::setFramesPerTexture(unsigned int frames)
{
    framesPerTexture = frames;
}

Animation::~Animation()
{
    textures.clear();
}

std::string Animation::getName() const
{
    return name;
}


void Animation::setupTextures()
{
}

void Animation::setupEnvironment()
{
}

void Animation::deserialize(const Json::Value &obj)
{
    Json::FastWriter writer;
    Serializable::deserialize(obj);

    if (!obj.isMember("textures") || !obj["textures"].isArray()) {
        Logger::LogCritical("Animation::deserialize(const Json::Value &=<optimized out>): JSON object must have an member \"textures\" of type array. Deserialization aborted");
        return;
    }

    for (auto &texture : obj["textures"]) {
        addTexture(GameSerializer::deserialize<Texture>(texture));
    }

    if (!obj.isMember("name")) {
        Logger::LogWarning("Animation::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"name\"");
    } else {
        name = obj["name"].asString();
    }

    if (!obj.isMember("frames_per_texture")) {
        Logger::LogWarning("Animation::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"frames_per_texture\"");
    } else {
        if (!obj["frames_per_texture"].isInt()) {
            Logger::LogError("Animation::deserialize(const Json::Value &=<optimized out>): Member \"frames_per_texture\" has to be an integer number. Value will be ignored");
        } else {
            framesPerTexture = obj["frames_per_texture"].asUInt();
        }
    }
}

Json::Value Animation::serialize() const
{
    Json::Value json;
    json["name"] = name;
    json["frames_per_texture"] = framesPerTexture;
    json["type"] = "ANIMATION";
    json["textures"] = Json::arrayValue;

    for (auto texture : textures) {
        json["textures"].append(texture->serialize());
    }

    json["active"] = currentTexture;
    return json;
}
