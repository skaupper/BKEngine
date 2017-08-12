#ifndef BKENGINE_GAMESERIALIZER_H
#define BKENGINE_GAMESERIALIZER_H

#include <memory>

#include <json/json.h>

#include "core/Game.h"
#include "serialization/Serializable.h"


namespace bkengine
{
    class GameSerializer
    {
        public:
            template <typename T>
            static std::shared_ptr<T> deserialize(const Json::Value &obj);

            template <typename T>
            static Json::Value serialize(const T &obj);
    };
}

#include "templates/GameSerializer_templates.h"

#endif
