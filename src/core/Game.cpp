#include "core/Game.h"

using namespace bkengine;


// FPS = 60
static const double SCREEN_TICKS_PER_FRAME = 1000. / 60.;


void Game::run()
{
    auto eventInterface = interfaceContainer.getEventInterface();
    auto settingsInterface = interfaceContainer.getSettingsInterface();
    auto graphicsInterface = interfaceContainer.getGraphicsInterface();

    if (graphicsInterface == nullptr) {
        throw GameLoopException("Game cannot be started because no graphics interface is set!");
    }

    if (eventInterface == nullptr) {
        throw GameLoopException("Game cannot be started because no event interface is set!");
    }

    if (settingsInterface == nullptr) {
        throw GameLoopException("Game cannot be started because no settings interface is set!");
    }

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

        uint64_t frameTicks = timer.getTicks();

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

bool Game::isRunning() const
{
    return running;
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
    auto graphicsInterface = interfaceContainer.getGraphicsInterface();
    if (graphicsInterface == nullptr) {
        throw NullPointerException("Failed to set icon file. Graphics interface is not set!");
    }
    graphicsInterface->setIcon(file);
}

void Game::setWindowSize(Size size)
{
    auto graphicsInterface = interfaceContainer.getGraphicsInterface();
    if (graphicsInterface == nullptr) {
        throw NullPointerException("Failed to set window size. Graphics interface is not set!");
    }
    graphicsInterface->setWindowSize(size);
}

void Game::setWindowTitle(const std::string &title)
{
    auto graphicsInterface = interfaceContainer.getGraphicsInterface();
    if (graphicsInterface == nullptr) {
        throw NullPointerException("Failed to set window title. Graphics interface is not set!");
    }
    graphicsInterface->setWindowTitle(title);
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
