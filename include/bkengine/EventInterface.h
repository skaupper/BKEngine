#ifndef EVENT_INTERFACE_H
#define EVENT_INTERFACE_H

#include "Event.h"

namespace bkengine
{
    class EventInterface
    {
        public:
            virtual bool ready() = 0;
            virtual Event poll() = 0;
    };
}

#endif
