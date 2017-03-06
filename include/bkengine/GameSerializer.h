#ifndef BKENGINE_GAMESERIALIZER_H
#define BKENGINE_GAMESERIALIZER_H

#include <memory>

#include <json/json.h>

#include "Serializable.h"


namespace bkengine
{
    class Game;
    class Scene;
    class Element;
    class Animation;
    class Texture;

    class GameSerializer
    {
        public:
            template <typename T> static std::shared_ptr<T> deserialize(
                const Json::Value &obj);
    };
}

#endif
