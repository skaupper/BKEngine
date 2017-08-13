#ifndef BKENGINE_BUILDER_EXCEPTION_H
#define BKENGINE_BUILDER_EXCEPTION_H

#include <stdexcept>


namespace bkengine
{
    class BuilderException : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };
}

#endif  // BKENGINE_BUILDER_EXCEPTION_H