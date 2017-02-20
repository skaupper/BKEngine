#ifndef GAME_TEMPLATES_H
#define GAME_TEMPLATES_H

template <typename T> T &Game::addScene(const T &scene)
{
    return addScene<T>(std::make_shared<T>(std::move((T &) scene)));
}

template <typename T> T &Game::addScene(const std::shared_ptr<T> &scene)
{
    scenes.push_back(scene);

    if (scenes.size() == 1) {
        activeScene = 0;
    }

    return *((T *) scenes.back().get());
}

template <typename T, typename... Params> T &Game::addScene(Params... params)
{
    return addScene<T>(std::make_shared<T>(params...));
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
    if (activeScene == -1) {
        Logger::LogCritical("Game::getCurrentScene(): Scene not found");
        throw "No scene added";
    }

    return *((T *) scenes[activeScene].get());
}

#endif
