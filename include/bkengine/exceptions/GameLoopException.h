#ifndef BKENGINE_GAME_LOOP_EXCEPTION_H
#define BKENGINE_GAME_LOOP_EXCEPTION_H

#include <stdexcept>


namespace bkengine
{
    class GameLoopException : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };
}

#endif  // BKENGINE_GAME_LOOP_EXCEPTION_H