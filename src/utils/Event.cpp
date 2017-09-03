#include "utils/Event.h"

using namespace bkengine;

static void copy(Event &e1, const Event &e2)
{
    e1.type = e2.type;
    e1.timeStamp = e2.timeStamp;
    e1.windowId = e2.windowId;

    switch (e1.type) {
        case EventType::KEYBOARD:
            new (&e1.keyboard) KeyboardEvent(e2.keyboard);
            break;

        case EventType::MOUSE:
            new (&e1.mouse) MouseEvent(e2.mouse);
            break;

        case EventType::MOTION:
            new (&e1.motion) MotionEvent(e2.motion);
            break;

        case EventType::WHEEL:
            new (&e1.wheel) WheelEvent(e2.wheel);
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
