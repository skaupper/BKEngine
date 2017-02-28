#ifndef BKENGINE_EVENT_H
#define BKENGINE_EVENT_H

#include <chrono>

#include "Keys.h"


namespace bkengine
{
    enum class KeyState {
        NONE,
        DOWN,
        UP
    };

    typedef KeyState ButtonState;

    enum class WheelDirection {
        NORMAL,
        FLIPPED
    };

    enum class EventType {
        UNKNOWN,
        KEYBOARD,
        MOUSE,
        MOTION,
        WHEEL,
        QUIT
    };


    struct KeyboardEvent {
        Keys key;
        KeyState state;
        bool repeat;
    };

    struct MouseEvent {
        ButtonState state;
        Buttons button;
        uint8_t specialId;
        uint8_t clicks;
        int32_t x;
        int32_t y;
    };

    struct MotionEvent {
        int32_t x;
        int32_t y;
        int32_t relativeX;
        int32_t relativeY;
    };

    struct WheelEvent {
        int32_t x;
        int32_t y;
        WheelDirection direction;
    };

    struct WindowEvent {
        // TODO: implement
    };

    class Event
    {
        public:
            Event() {}
            virtual ~Event() {}
            Event(const Event &event);
            Event &operator=(const Event &event);

            EventType type = EventType::UNKNOWN;
            uint32_t timeStamp = std::chrono::duration_cast<std::chrono::seconds>
                                 (std::chrono::system_clock::now().time_since_epoch()).count();
            uint32_t windowId = 0;

            union {
                KeyboardEvent keyboard;
                MouseEvent mouse;
                MotionEvent motion;
                WheelEvent wheel;
                WindowEvent window;
            };
    };
}

#endif
