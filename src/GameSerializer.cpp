#include "GameSerializer.h"

using namespace bkengine;


Json::Value GameSerializer::serializeGame(const Game &game)
{
    auto json = game.serialize();
    json["scenes"] = Json::arrayValue;

    for (auto scene : game.scenes) {
        json["scenes"].append(serializeScene(*scene));
    }

    json["active_scene"] = game.activeScene;
    return json;
}

Json::Value GameSerializer::serializeScene(const Scene &scene)
{
    auto json = scene.serialize();
    json["elements"] = Json::arrayValue;

    for (auto element : scene.elements) {
        json["elements"].append(serializeElement(*element));
    }

    return json;
}

Json::Value GameSerializer::serializeElement(const Element &element)
{
    auto json = element.serialize();
    json["animations"] = Json::arrayValue;

    for (auto animation : element.animations) {
        json["animations"].append(serializeAnimation(*animation));
    }

    return json;
}

Json::Value GameSerializer::serializeAnimation(const Animation &animation)
{
    auto json = animation.serialize();
    json["textures"] = Json::arrayValue;

    for (auto texture : animation.textures) {
        json["textures"].append(serializeTexture(*texture));
    }

    return json;
}

Json::Value GameSerializer::serializeTexture(const Texture &texture)
{
    return texture.serialize();
}

std::shared_ptr<Game> GameSerializer::deserializeGame(const Json::Value &obj)
{
    auto game = Serializer::getInstance<Game>(obj["type"].asString());
    game->deserialize(obj);

    for (auto &scene : obj["scenes"]) {
        game->addScene(deserializeScene(scene));
    }

    game->activate(obj["active_scene"].asInt());
    return game;
}

std::shared_ptr<Scene> GameSerializer::deserializeScene(const Json::Value &obj)
{
    auto scene = Serializer::getInstance<Scene>(obj["type"].asString());
    scene->deserialize(obj);

    for (auto &element : obj["elements"]) {
        scene->addElement(deserializeElement(element));
    }

    return scene;
}

std::shared_ptr<Element> GameSerializer::deserializeElement(
    const Json::Value &obj)
{
    auto element = Serializer::getInstance<Element>(obj["type"].asString());
    element->deserialize(obj);

    for (auto &animation : obj["animations"]) {
        element->addAnimation(deserializeAnimation(animation));
    }

    return element;
}

std::shared_ptr<Animation> GameSerializer::deserializeAnimation(
    const Json::Value &obj)
{
    auto animation = Serializer::getInstance<Animation>(obj["type"].asString());
    animation->deserialize(obj);

    for (auto &texture : obj["textures"]) {
        animation->addTexture(deserializeTexture(texture));
    }

    return animation;
}

std::shared_ptr<Texture> GameSerializer::deserializeTexture(
    const Json::Value &obj)
{
    auto texture = Serializer::getInstance<Texture>(obj["type"].asString());
    texture->deserialize(obj);
    return texture;
}