namespace bkengine
{
    template <>
    std::shared_ptr<Game> GameSerializer::deserialize(const Json::Value &obj)
    {
        if (!obj.isMember("type")) {
            Logger::LogCritical("GameSerializer::deserialize<Game>(const Json::Value &=<optimized out>): "
                                "JSON does not contain the required attribute 'type'!");
            return nullptr;
        }
        
        auto tmp = Serializer::getInstance<Game>(obj["type"].asString());
        tmp->deserialize(obj);
        return tmp;
    }

    template <>
    std::shared_ptr<Scene> GameSerializer::deserialize(const Json::Value &obj)
    {
        if (!obj.isMember("type")) {
            Logger::LogCritical("GameSerializer::deserialize<Scene>(const Json::Value &=<optimized out>): "
                                "JSON does not contain the required attribute 'type'!");
            return nullptr;
        }

        auto tmp = Serializer::getInstance<Scene>(obj["type"].asString());
        tmp->deserialize(obj);
        return tmp;
    }

    template <>
    std::shared_ptr<Element> GameSerializer::deserialize(const Json::Value &obj)
    {
        if (!obj.isMember("type")) {
            Logger::LogCritical("GameSerializer::deserialize<Element>(const Json::Value &=<optimized out>): "
                                "JSON does not contain the required attribute 'type'!");
            return nullptr;
        }
        
        auto tmp = Serializer::getInstance<Element>(obj["type"].asString());
        tmp->deserialize(obj);
        return tmp;
    }

    template <>
    std::shared_ptr<Animation> GameSerializer::deserialize(const Json::Value &obj)
    {
        if (!obj.isMember("type")) {
            Logger::LogCritical("GameSerializer::deserialize<Animation>(const Json::Value &=<optimized out>): "
                                "JSON does not contain the required attribute 'type'!");
            return nullptr;
        }
        
        auto tmp = Serializer::getInstance<Animation>(obj["type"].asString());
        tmp->deserialize(obj);
        return tmp;
    }

    template <>
    std::shared_ptr<Texture> GameSerializer::deserialize(const Json::Value &obj)
    {
        if (!obj.isMember("type")) {
            Logger::LogCritical("GameSerializer::deserialize<Texture>(const Json::Value &=<optimized out>): "
                                "JSON does not contain the required attribute 'type'!");
            return nullptr;
        }
        
        auto tmp = Serializer::getInstance<Texture>(obj["type"].asString());
        tmp->deserialize(obj);
        return tmp;
    }
}
