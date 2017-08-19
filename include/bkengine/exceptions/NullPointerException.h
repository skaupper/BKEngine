#ifndef BKENGINE_NULL_POINTER_EXCEPTION_H
#define BKENGINE_NULL_POINTER_EXCEPTION_H

#include <stdexcept>


namespace bkengine
{
    class NullPointerException : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };
}

#endif  // BKENGINE_NULL_POINTER_EXCEPTION_H