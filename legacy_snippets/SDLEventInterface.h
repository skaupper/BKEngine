#ifndef BKENGINE_SDLEVENTINTERFACE_H
#define BKENGINE_SDLEVENTINTERFACE_H

#include "interfaces/EventInterface.h"
#include "utils/Logger.h"


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
