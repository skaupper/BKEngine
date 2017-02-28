#include "Game.h"
#include "SDLEventInterface.h"
#include "INISettingsInterface.h"

using namespace bkengine;


//FPS = 60
static const float SCREEN_TICKS_PER_FRAME = 1000 / 60;


Game::Game(int width, int height, const std::string &title) : activeScene(-1),
    running(false), eventInterface(nullptr)
{
    Core::getInstance(width, height, title);
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
        if (scene->getName() == name) {
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
        if (scene->getName() == name) {
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
        if (scene->getName() == name) {
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

    setup();

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

void Game::setup()
{
}

void Game::teardown()
{
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
