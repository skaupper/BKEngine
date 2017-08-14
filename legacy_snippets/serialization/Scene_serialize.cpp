/*
void Scene::deserialize(const Json::Value &obj)
{
    Json::FastWriter writer;
    Serializable::deserialize(obj);

    if (!obj.isMember("name")) {
        Logger::LogWarning("Scene::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"name\"");
    } else {
        name = obj["name"].asString();
    }

    if (!obj.isMember("elements") || !obj["elements"].isArray()) {
        Logger::LogCritical("Scene::deserialize(const Json::Value &=<optimized out>): JSON object must have an member \"elements\" of type array. Deserialization aborted");
        return;
    }

    for (auto &element : obj["elements"]) {
        auto e = GameSerializer::deserialize<Element>(element);
        e->parentScene = this;
        e->setupEnvironment();
        addElement(e);
    }
}

Json::Value Scene::serialize() const
{
    Json::Value json;
    json["name"] = name;
    json["type"] = "SCENE";
    json["elements"] = Json::arrayValue;

    for (auto element : elements) {
        json["elements"].append(element->serialize());
    }

    return json;
}
*/