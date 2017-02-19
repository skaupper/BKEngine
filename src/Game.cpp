#include "Game.h"

using namespace bkengine;


//FPS = 60
static const float SCREEN_TICKS_PER_FRAME = 1000 / 60;


Game::Game(int width, int height, const std::string &title) : activeScene(-1), running(false)
{
    Core::getInstance(width, height, title);
}

Game::~Game()
{
    scenes.clear();
}

void Game::setActiveScene(const std::string &name)
{
    int index = 0;

    for (auto &scene : scenes) {
        if (scene->getName() == name) {
            activeScene = index;
            return;
        }

        index++;
    }

    Logger::LogCritical("Game::setActiveScene(const std::string &=" + name +
                        "): Scene not found");
    throw "Scene not found";
}

void Game::setActiveScene(unsigned int index)
{
    if (index < scenes.size()) {
        activeScene = index;
    } else {
        Logger::LogCritical("Game::setActiveScene(int=" + std::to_string(
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

int Game::run()
{
    int status = Core::getInstance()->setup();

    if (status != 0) {
        return status;
    }

    SDL_Event event;
    Timer timer;
    running = true;

    while (running) {
        timer.start();

        while (MANGLE_SDL(SDL_PollEvent)(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            status = onEvent(&event);

            if (status != 0) {
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

    return 0;
}

void Game::stop()
{
    running = false;
}


void Game::onLoop()
{
    if (activeScene > -1) {
        getCurrentScene<Scene>().onLoop();
    }
}

int Game::onEvent(SDL_Event *event)
{
    if (activeScene > -1) {
        int status = getCurrentScene<Scene>().onEvent(event);

        if (status != 0) {
            return status;
        }
    }

    return 0;
}

void Game::onRender()
{
    if (activeScene > -1) {
        MANGLE_SDL(SDL_RenderClear)(Core::getInstance()->getRenderer());
        getCurrentScene<Scene>().onRender();
        MANGLE_SDL(SDL_RenderPresent)(Core::getInstance()->getRenderer());
    }
}
