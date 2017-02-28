#ifndef BKENGINE_EVENTINTERFACE_H
#define BKENGINE_EVENTINTERFACE_H

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
