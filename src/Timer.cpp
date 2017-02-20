#include "Timer.h"

using namespace bkengine;


Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    if (!started) {
        started = true;
        paused = false;
        startTicks = MANGLE_SDL(SDL_GetTicks)();
        pausedTicks = 0;
    }
}

void Timer::stop()
{
    started = false;
    paused = false;
    startTicks = 0;
    pausedTicks = 0;
}

void Timer::pause()
{
    if (started && !paused) {
        paused = true;
        pausedTicks = MANGLE_SDL(SDL_GetTicks)() - startTicks;
        startTicks = 0;
    }
}

void Timer::unpause()
{
    if (started && paused) {
        paused = false;
        startTicks = MANGLE_SDL(SDL_GetTicks)() - pausedTicks;
        pausedTicks = 0;
    }
}

int Timer::getTicks() const
{
    int time = 0;

    if (started) {
        if (paused) {
            time = pausedTicks;
        } else {
            time = MANGLE_SDL(SDL_GetTicks)() - startTicks;
        }
    }

    return time;
}

bool Timer::isStarted() const
{
    return started;
}

bool Timer::isPaused() const
{
    return paused && started;
}
