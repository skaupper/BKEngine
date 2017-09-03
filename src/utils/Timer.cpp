#include "utils/Timer.h"

using namespace bkengine;

uint64_t getMilliseconds()
{
    auto duration = std::chrono::high_resolution_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

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
        startTicks = getMilliseconds();
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
        pausedTicks = getMilliseconds();
        startTicks = 0;
    }
}

void Timer::unpause()
{
    if (started && paused) {
        paused = false;
        startTicks = getMilliseconds();
        pausedTicks = 0;
    }
}

uint64_t Timer::getTicks() const
{
    uint64_t time = 0;

    if (started) {
        if (paused) {
            time = pausedTicks;
        } else {
            time = getMilliseconds();
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
