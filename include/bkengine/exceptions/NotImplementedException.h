#ifndef BKENGINE_NOTIMPLEMENTEDEXCEPTION_H
#define BKENGINE_NOTIMPLEMENTEDEXCEPTION_H

#include <stdexcept>

namespace bkengine
{
    class NotImplementedException : public std::logic_error
    {
    public:
        NotImplementedException() : std::logic_error("Function not yet implemented.") { };
    };
}

#endif //BKENGINE_NOTIMPLEMENTEDEXCEPTION_H