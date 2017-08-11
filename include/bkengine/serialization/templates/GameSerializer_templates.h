namespace bkengine
{
    template <>
    std::shared_ptr<Game> GameSerializer::deserialize(const Json::Value &obj)
    {
        auto tmp = Serializer::getInstance<Game>(obj["type"].asString());
        tmp->deserialize(obj);
        return tmp;
    }

    template <>
    std::shared_ptr<Scene> GameSerializer::deserialize(const Json::Value &obj)
    {
        auto tmp = Serializer::getInstance<Scene>(obj["type"].asString());
        tmp->deserialize(obj);
        return tmp;
    }

    template <>
    std::shared_ptr<Element> GameSerializer::deserialize(const Json::Value &obj)
    {
        auto tmp = Serializer::getInstance<Element>(obj["type"].asString());
        tmp->deserialize(obj);
        return tmp;
    }

    template <>
    std::shared_ptr<Animation> GameSerializer::deserialize(const Json::Value &obj)
    {
        auto tmp = Serializer::getInstance<Animation>(obj["type"].asString());
        tmp->deserialize(obj);
        return tmp;
    }

    template <>
    std::shared_ptr<Texture> GameSerializer::deserialize(const Json::Value &obj)
    {
        auto tmp = Serializer::getInstance<Texture>(obj["type"].asString());
        tmp->deserialize(obj);
        return tmp;
    }
}
