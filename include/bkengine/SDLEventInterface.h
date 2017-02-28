#ifndef BKENGINE_SDLEVENTINTERFACE_H
#define BKENGINE_SDLEVENTINTERFACE_H

#include <map>

#include "SDLWrapper.h"
#include "EventInterface.h"
#include "Logger.h"

namespace bkengine
{
    class SDLEventInterface : public EventInterface
    {
        public:
            virtual bool ready();
            virtual Event poll();
    };
}

#endif
