#ifndef BKENGINE_NAME_ALREADY_EXISTS_EXCEPTION_H
#define BKENGINE_NAME_ALREADY_EXISTS_EXCEPTION_H

#include <stdexcept>


namespace bkengine
{
    class NameAlreadyExistsException : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };
}

#endif  // BKENGINE_NAME_ALREADY_EXISTS_EXCEPTION_H