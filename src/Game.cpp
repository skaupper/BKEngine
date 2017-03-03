#include "Game.h"
#include "SDLEventInterface.h"
#include "INISettingsInterface.h"

using namespace bkengine;


//FPS = 60
static const float SCREEN_TICKS_PER_FRAME = 1000 / 60;


Game::Game() : Game(1024, 768, "TEST WINDOW")
{

}

Game::Game(int width, int height, const std::string &title) :
    activeScene(-1),
    eventInterface(nullptr),
    running(false)
{
    Core::createInstance(width, height, title);
}

Game::~Game()
{
    teardown();
    clear();
}

void Game::activate(const std::string &name)
{
    int index = 0;

    for (auto &scene : scenes) {
        if (scene->getDescription() == name) {
            activeScene = index;
            return;
        }

        index++;
    }

    Logger::LogCritical("Game::activate(const std::string &=" + name +
                        "): Scene not found");
    throw "Scene not found";
}

void Game::activate(unsigned int index)
{
    if (index < scenes.size()) {
        activeScene = index;
    } else {
        Logger::LogCritical("Game::activate(int=" + std::to_string(
                                index) + "): Scene not found");
        throw "Scene not found";
    }
}

bool Game::hasScene(const std::string &name) const
{
    for (auto &scene : scenes) {
        if (scene->getDescription() == name) {
            return true;
        }
    }

    return false;
}

bool Game::hasScene(unsigned int index) const
{
    return index < scenes.size();
}

void Game::removeScene(const std::string &name)
{
    int index = 0;

    for (auto &scene : scenes) {
        if (scene->getDescription() == name) {
            scenes.erase(scenes.begin() + index);
            return;
        }

        index++;
    }

    Logger::LogCritical("Game::removeScene(const std::string &=" + name +
                        "): Scene not found");
    throw "Scene not found";
}

void Game::removeScene(unsigned int index)
{
    if (index < scenes.size()) {
        scenes.erase(scenes.begin() + index);
    } else {
        Logger::LogCritical("Game::removeScene(int=" + std::to_string(
                                index) + "): Scene not found");
        throw "Scene not found";
    }
}

Scene &Game::getScene(const std::string &name)
{
    return getScene<Scene>(name);
}

Scene &Game::getScene(unsigned int index)
{
    return getScene<Scene>(index);
}

Scene &Game::getCurrentScene()
{
    return getCurrentScene<Scene>();
}

std::shared_ptr<SettingsInterface> Game::getSettingsInterface()
{
    return settingsInterface;
}

bool Game::hasData(const std::string &name)
{
    return dataStore.find(name) != dataStore.end();
}

void Game::resizeWindow(int windowWidth, int windowHeight)
{
    Core::getInstance()->resizeWindow(windowWidth, windowHeight);
}

void Game::setWindowTitle(const std::string &title)
{
    Core::getInstance()->setWindowTitle(title);
}

void Game::run()
{
    if (!Core::getInstance()->initEnvironment()) {
        return;
    }

    if(scenes.size() == 0) {
        setupScenes();
    }
    setupEnvironment();

    if (eventInterface == nullptr) {
        Logger::LogInfo("Game::run(): No event interface set. SDLEventInterface will be used.");
        setEventInterface<SDLEventInterface>();
    }

    if (settingsInterface == nullptr) {
        Logger::LogInfo("Game::run(): No settings interface set. INISettingsInterface will be used.");
        setSettingsInterface<INISettingsInterface>();
    }

    Timer timer;
    running = true;

    while (running) {
        timer.start();

        while (eventInterface->ready()) {
            Event event = eventInterface->poll();

            if (event.type == EventType::QUIT) {
                running = false;
                Logger::LogDebug("Game::run(): event is SDL_QUIT");
            }

            if (!onEvent(event)) {
                Logger::LogDebug("Game::run(): onEvent returned false");
                running = false;
                break;
            }
        }

        onLoop();
        onRender();
        int frameTicks = timer.getTicks();

        if (frameTicks < SCREEN_TICKS_PER_FRAME) {
            MANGLE_SDL(SDL_Delay)(SCREEN_TICKS_PER_FRAME - frameTicks);
        }

        timer.stop();
    }

    teardown();
}

void Game::stop()
{
    running = false;
}

bool Game::setIcon(const std::string &iconPath)
{
    return Core::getInstance()->setIcon(iconPath);
}

void Game::clear()
{
    scenes.clear();
    dataStore.clear();
}

void Game::setupEnvironment()
{
}

void Game::setupScenes()
{
}

void Game::teardown()
{
}

void Game::deserialize(const Json::Value &obj)
{
    Serializable::deserialize(obj);
    std::string eventInterface = obj["interfaces"]["event"].asString();
    std::string settingsInterface = obj["interfaces"]["settings"].asString();

    if (!eventInterface.empty()) {
        this->eventInterface = Serializer::getInstance<EventInterface>(eventInterface);
    }

    if (!settingsInterface.empty()) {
        this->settingsInterface = Serializer::getInstance<SettingsInterface>(settingsInterface);
    }

    for(auto font : obj["fonts"]) {
        Fonts::registerFont(font["file"].asString(), 1, font["name"].asString());
    }

    for (auto &scene : obj["scenes"]) {
        auto s = GameSerializer::deserialize<Scene>(scene);
        s->parentGame = this;
        s->setupEnvironment();
        addScene(s);
    }
    int width = obj["window"]["width"].asInt();
    int height = obj["window"]["height"].asInt();
    std::string title = obj["window"]["title"].asString();
    Core::createInstance(width, height, title);

    setupEnvironment();
    activate(obj["active_scene"].asInt());
}

Json::Value Game::serialize() const
{
    Json::Value json;
    // TODO: use any kind of dynamic approach
    json["interfaces"]["settings"] = "ini";
    json["interfaces"]["event"] = "sdl_event";
    json["fonts"] = Json::arrayValue;
    for(auto font : Fonts::fontFileCache) {
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

    json["active_scene"] = activeScene;

    Rect windowSize = Core::getInstance()->getWindowSize();
    json["window"]["width"] = (int) windowSize.w;
    json["window"]["height"] = (int) windowSize.h;
    json["window"]["title"] = Core::getInstance()->getWindowTitle();
    return json;
}

void Game::onLoop()
{
    if (activeScene > -1) {
        getCurrentScene<Scene>().onLoop();
    }
}

bool Game::onEvent(const Event &event)
{
    if (activeScene > -1 && !getCurrentScene<Scene>().onEvent(event)) {
        return false;
    }

    return true;
}

void Game::onRender()
{
    if (activeScene > -1) {
        MANGLE_SDL(SDL_RenderClear)(Core::getInstance()->getRenderer());
        getCurrentScene<Scene>().onRender();
        MANGLE_SDL(SDL_RenderPresent)(Core::getInstance()->getRenderer());
    }
}
