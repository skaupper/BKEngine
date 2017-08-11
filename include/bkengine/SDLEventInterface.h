#ifndef BKENGINE_SDLEVENTINTERFACE_H
#define BKENGINE_SDLEVENTINTERFACE_H

#include <map>

#include "interfaces/EventInterface.h"
#include "utils/Logger.h"
#include "SDLWrapper.h"


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
