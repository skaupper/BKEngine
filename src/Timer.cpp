#include "Timer.h"

using namespace bkengine;


Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

// Startet den Timer
void Timer::start()
{
    if (!started) {
        started = true;
        paused = false;
        startTicks = MANGLE_SDL(SDL_GetTicks)();
        pausedTicks = 0;
    }
}

// Stoppt den Timer
void Timer::stop()
{
    started = false;
    paused = false;
    startTicks = 0;
    pausedTicks = 0;
}

// Pausiert den Timer
void Timer::pause()
{
    if (started && !paused) {
        paused = true;
        pausedTicks = MANGLE_SDL(SDL_GetTicks)() - startTicks;
        startTicks = 0;
    }
}

// Entpausiert den Timer
void Timer::unpause()
{
    if (started && paused) {
        paused = false;
        startTicks = MANGLE_SDL(SDL_GetTicks)() - pausedTicks;
        pausedTicks = 0;
    }
}

// Gibt die Ticks des Timers zur�ck
int Timer::getTicks()
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

bool Timer::isStarted()
{
    //Timer is running and paused or unpaused
    return started;
}

bool Timer::isPaused()
{
    //Timer is running and paused
    return paused && started;
}
