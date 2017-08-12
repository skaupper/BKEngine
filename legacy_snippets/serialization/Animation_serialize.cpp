/*
void Animation::deserialize(const Json::Value &obj)
{
    Json::FastWriter writer;
    Serializable::deserialize(obj);

    if (!obj.isMember("textures") || !obj["textures"].isArray()) {
        Logger::LogCritical("Animation::deserialize(const Json::Value &=<optimized out>): JSON object must have an
member \"textures\" of type array. Deserialization aborted");
        return;
    }

    for (auto &texture : obj["textures"]) {
        addTexture(GameSerializer::deserialize<Texture>(texture));
    }

    if (!obj.isMember("name")) {
        Logger::LogWarning("Animation::deserialize(const Json::Value &=<optimized out>): JSON object has no member
\"name\"");
    } else {
        name = obj["name"].asString();
    }

    if (!obj.isMember("frames_per_texture")) {
        Logger::LogWarning("Animation::deserialize(const Json::Value &=<optimized out>): JSON object has no member
\"frames_per_texture\"");
    } else {
        if (!obj["frames_per_texture"].isInt()) {
            Logger::LogError("Animation::deserialize(const Json::Value &=<optimized out>): Member \"frames_per_texture\"
has to be an integer number. Value will be ignored");
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

*/