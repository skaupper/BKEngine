template <typename T> T Game::create(const InterfaceContainer &interfaces,
                                     int width, int height,
                                     const std::string &title)
{
    Game g(interfaces, width, height, title);
    g.setupScenes();
    g.setupEnvironment();
    g.backup();
    return g;
}

template <typename T> T &Game::addScene(const T &scene)
{
    return addScene<T>(std::make_shared<T>(std::move((T &) scene)));
}

template <typename T> T &Game::addScene(const std::shared_ptr<T> &scene)
{
    scenes.push_back(scene);

    if (scenes.size() == 1) {
        currentScene = 0;
    }

    return *((T *) scenes.back().get());
}

template <typename T, typename... Params> T &Game::addScene(Params... params)
{
    auto scene = std::make_shared<T>(this, params...);
    scene->setupElements();
    scene->setupEnvironment();
    scene->backup();
    return addScene<T>(scene);
}


template <typename T> T &Game::getScene(const std::string &name)
{
    for (auto &scene : scenes) {
        if (scene->getName() == name) {
            return *((T *) scene.get());
        }
    }

    Logger::LogCritical("Game::getScene(const std::string &=" + name +
                        "): Scene not found");
    throw "Scene not found";
}

template <typename T> T &Game::getScene(unsigned int index)
{
    if (index < scenes.size()) {
        return *((T *) scenes[index].get());
    }

    Logger::LogCritical("Game::getScene(int=" + std::to_string(
                            index) + "): Scene not found");
    throw "Scene not found";
}

template <typename T> T &Game::getCurrentScene()
{
    if (currentScene == -1) {
        Logger::LogCritical("Game::getCurrentScene(): Scene not found");
        throw "No scene added";
    }

    return *((T *) scenes[currentScene].get());
}

template <typename T> T &Game::getData(const std::string &name)
{
    if (!hasData(name)) {
        Logger::LogCritical("Game::getData(const std::string &=" + name +
                            "): Data not found");
        throw "Data not found";
    }

    return *((T *) dataStore[name].get());
}

template <typename T> T &Game::addData(const std::string &name)
{
    dataStore[name] = std::static_pointer_cast<Storage>
                      (std::make_shared<T>("test"));
    return getData<T>(name);
}