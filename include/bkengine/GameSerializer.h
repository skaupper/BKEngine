#ifndef BKENGINE_GAMESERIALIZER_H
#define BKENGINE_GAMESERIALIZER_H

#include <memory>

#include <json/json.h>

#include "Game.h"


namespace bkengine
{
    class GameSerializer
    {
    public:
        static Json::Value serializeGame(const Game &);
        static Json::Value serializeScene(const Scene &);
        static Json::Value serializeElement(const Element &);
        static Json::Value serializeAnimation(const Animation &);
        static Json::Value serializeTexture(const Texture &);
        
        static std::shared_ptr<Game> deserializeGame(const Json::Value &obj);
        static std::shared_ptr<Scene> deserializeScene(const Json::Value &obj);
        static std::shared_ptr<Element> deserializeElement(const Json::Value &obj);
        static std::shared_ptr<Animation> deserializeAnimation(const Json::Value &obj);
        static std::shared_ptr<Texture> deserializeTexture(const Json::Value &obj);
    };
}

#endif