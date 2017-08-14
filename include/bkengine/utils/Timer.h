#ifndef BKENGINE_TIMER_H
#define BKENGINE_TIMER_H

#include <chrono>


namespace bkengine
{
    class Timer
    {
        private:
            uint64_t startTicks;
            uint64_t pausedTicks;
            bool paused;
            bool started;

        public:
            Timer();
            void start();
            void stop();
            void pause();
            void unpause();
            uint64_t getTicks() const;
            bool isStarted() const;
            bool isPaused() const;
    };
}

#endif
