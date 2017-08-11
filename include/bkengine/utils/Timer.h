#ifndef BKENGINE_TIMER_H
#define BKENGINE_TIMER_H

#include "SDLWrapper.h"

namespace bkengine
{
    class Timer
    {
        private:
            int startTicks;
            int pausedTicks;
            bool paused;
            bool started;

        public:
            Timer();
            void start();
            void stop();
            void pause();
            void unpause();
            int getTicks() const;
            bool isStarted() const;
            bool isPaused() const;
    };
}

#endif
