#include "core/Game.h"

using namespace bkengine;


// FPS = 60
static const double SCREEN_TICKS_PER_FRAME = 1000. / 60;


void Game::run()
{
    auto eventInterface = interfaceContainer.getEventInterface();
    auto settingsInterface = interfaceContainer.getSettingsInterface();
    auto graphicsInterface = interfaceContainer.getGraphicsInterface();

    Timer timer;
    running = true;

    while (running) {
        timer.start();

        while (eventInterface->ready()) {
            Event event = eventInterface->poll();

            if (event.type == EventType::QUIT) {
                running = false;
                Logger::debug << "Game::run(): event has type EventType::QUIT";
            }

            _onEvent(event);
        }

        _onLoop();
        _onRender();

        int frameTicks = timer.getTicks();

        if (frameTicks < SCREEN_TICKS_PER_FRAME) {
            graphicsInterface->delay(SCREEN_TICKS_PER_FRAME - frameTicks);
        }

        timer.stop();
    }
}

void Game::stop()
{
    running = false;
}

bool Game::onRender()
{
    return false;
}

bool Game::onLoop()
{
    return false;
}

bool Game::onEvent(const Event &event)
{
    return false;
}


void Game::setIconFile(const std::string &file)
{
    interfaceContainer.getGraphicsInterface()->setIcon(file);
}

void Game::setWindowSize(Size size)
{
    interfaceContainer.getGraphicsInterface()->setWindowSize(size);
}

void Game::setWindowTitle(const std::string &title)
{
    interfaceContainer.getGraphicsInterface()->setWindowTitle(title);
}


void Game::_onRender()
{
    bool suppress = onRender();
    if (suppress) {
        return;
    }

    if (currentScene) {
        auto graphicsInterface = interfaceContainer.getGraphicsInterface();
        graphicsInterface->clear();
        currentScene->_onRender();
        graphicsInterface->draw();
    }
}

void Game::_onLoop()
{
    bool suppress = onLoop();
    if (suppress) {
        return;
    }

    if (currentScene) {
        currentScene->_onLoop();
    }
}

void Game::_onEvent(const Event &event)
{
    bool suppress = onEvent(event);
    if (suppress) {
        return;
    }

    if (currentScene) {
        currentScene->_onEvent(event);
    }
}
