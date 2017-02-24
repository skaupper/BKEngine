#include "Event.h"

using namespace bkengine;

static void copy(Event &e1, const Event &e2)
{
    e1.type = e2.type;
    e1.timeStamp = e2.timeStamp;
    e1.windowId = e2.windowId;
    switch(e1.type) {
        case EventType::KEYBOARD:
            e1.keyboard = e2.keyboard;
            break;

        case EventType::MOUSE:
            e1.mouse = e2.mouse;
            break;

        case EventType::MOTION:
            e1.motion = e2.motion;
            break;

        case EventType::WHEEL:
            e1.wheel = e2.wheel;
            break;

        case EventType::UNKNOWN:
        case EventType::QUIT:
            break;
    }
}

Event::Event(const Event &event)
{
    copy(*this, event);
}

Event &Event::operator=(const Event &event)
{
    copy(*this, event);
    return *this;
}
