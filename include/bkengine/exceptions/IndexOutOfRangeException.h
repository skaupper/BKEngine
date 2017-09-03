#ifndef BKENGINE_INDEX_OUT_OF_RANGE_EXCEPTION_H
#define BKENGINE_INDEX_OUT_OF_RANGE_EXCEPTION_H

#include <stdexcept>


namespace bkengine
{
    class IndexOutOfRangeException : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };
}

#endif  // BKENGINE_INDEX_OUT_OF_RANGE_EXCEPTION_H