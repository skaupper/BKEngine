
    /*
void Game::deserialize(const Json::Value &obj)
{
    // TODO: serialization!
    Json::FastWriter writer;
    Serializable::deserialize(obj);
    
    if (!obj.isMember("interfaces")) {
        Logger::LogWarning("Game::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"interfaces\". Default interfaces will be used");
    } else {
        auto jsonInterfaces = obj["interfaces"];
    
        if (!jsonInterfaces.isMember("event")) {
            Logger::LogWarning("Game::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"interfaces\".\"event\". Default event interface will be used");
        } else {
            eventInterface = Serializer::getInstance<EventInterface>
                             (jsonInterfaces["event"].asString());
        }
    
        if (!jsonInterfaces.isMember("settings")) {
            Logger::LogWarning("Game::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"interfaces\".\"settings\". Default settings interface will be used");
        } else {
            settingsInterface = Serializer::getInstance<SettingsInterface>
                                (jsonInterfaces["settings"].asString());
        }
    }
    
    if (!obj.isMember("fonts")) {
        Logger::LogWarning("Game::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"fonts\"");
    } else {
        for (auto font : obj["fonts"]) {
            if (!font.isMember("file") || !font.isMember("name")) {
                Logger::LogWarning("Game::deserialize(const Json::Value &=<optimized out>): A font object must have a \"file\" and a \"name\" member");
            } else {
                Fonts::registerFont(font["file"].asString(), 1, font["name"].asString());
            }
        }
    }
    
    int width = 1024;
    int height = 768;
    std::string title = "BKENGINE WINDOW";
    std::string icon = "";
    
    if (!obj.isMember("window")) {
        Logger::LogWarning("Game::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"window\". Default values will be used");
    } else {
        auto jsonWindow = obj["window"];
    
        if (!jsonWindow.isMember("width") || !jsonWindow["width"].isInt()) {
            Logger::LogError("Game::deserialize(const Json::Value &=<optimized out>): Member \"window\".\"width\" must be an integer. Default value will be used");
        } else {
            width = jsonWindow["width"].asInt();
        }
    
        if (!jsonWindow.isMember("height") || !jsonWindow["height"].isInt()) {
            Logger::LogError("Game::deserialize(const Json::Value &=<optimized out>): Member \"window\".\"height\" must be an integer. Default value will be used");
        } else {
            height = jsonWindow["height"].asInt();
        }
    
        if (!jsonWindow.isMember("title")) {
            Logger::LogError("Game::deserialize(const Json::Value &=<optimized out>): Member \"window\".\"height\" not found. Default value will be used");
        } else {
            title = jsonWindow["title"].asString();
        }
    
        if (!jsonWindow.isMember("icon")) {
            Logger::LogWarning("Game::deserialize(const Json::Value &=<optimized out>): Member \"window\".\"icon\" not found.");
        } else {
            icon = jsonWindow["icon"].asString();
        }
    }
    
    auto core = Core::createInstance(width, height, title);
    
    if (!icon.empty()) {
        core->setIcon(icon);
    }
    
    if (!obj.isMember("scenes") || !obj["scenes"].isArray()) {
        Logger::LogCritical("Game::deserialize(const Json::Value &=<optimized out>): JSON object must have an member \"scenes\" of type array. Deserialization aborted");
        return;
    }
    
    for (auto &scene : obj["scenes"]) {
        auto s = GameSerializer::deserialize<Scene>(scene);
        s->parentGame = this;
        s->setupEnvironment();
        addScene(s);
    }
    
    if (!obj.isMember("active")) {
        Logger::LogWarning("Game::deserialize(const Json::Value &=<optimized out>): JSON object has no member \"active\"");
    } else {
        auto jsonActive = obj["active"];
    
        if (jsonActive.isInt()) {
            activate(jsonActive.asInt());
        } else {
            activate(jsonActive.asString());
        }
    }
    
    setupEnvironment();
}

Json::Value Game::serialize() const
{
    Json::Value json;
    // TODO: serialization!
    // TODO: use any kind of dynamic approach
    json["interfaces"]["settings"] = "ini";
    json["interfaces"]["event"] = "sdl_event";
    json["fonts"] = Json::arrayValue;
    
    for (auto font : Fonts::fontFileCache) {
        Json::Value f;
        f["file"] = font.second;
        f["name"] = font.first;
        json["fonts"].append(f);
    }
    
    json["type"] = "GAME";
    json["scenes"] = Json::arrayValue;
    
    for (auto scene : scenes) {
        json["scenes"].append(scene->serialize());
    }
    
    Size windowSize = Core::getInstance()->getWindowSize();
    json["window"]["width"] = (int) windowSize.w;
    json["window"]["height"] = (int) windowSize.h;
    json["window"]["title"] = Core::getInstance()->getWindowTitle();
    json["active"] = currentScene;
    return json;
}
*/