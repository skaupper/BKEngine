#ifndef KEYS_H
#define KEYS_H

namespace bkengine
{
    enum class Keys {
        UNKNOWN,

        /* Control keys */
        RETURN,
        ESCAPE,
        BACKSPACE,
        TAB,
        SPACE,
        CAPSLOCK,

        /* Number keys */
        ZERO,
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,

        /* Letter keys */
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        /* Function keys */
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,

        /* Arrow keys */
        RIGHT,
        LEFT,
        DOWN,
        UP,

        PRINTSCREEN,
        SCROLLLOCK,
        PAUSE,
        INSERT,
        HOME,
        PAGEUP,
        DELETE,
        END,
        PAGEDOWN,

        /* Numpad keys */
        NUMLOCKCLEAR,
        NP_DIVIDE,
        NP_MULTIPLY,
        NP_MINUS,
        NP_PLUS,
        NP_ENTER,
        NP_ONE,
        NP_TWO,
        NP_THREE,
        NP_FOUR,
        NP_FIVE,
        NP_SIX,
        NP_SEVEN,
        NP_EIGHT,
        NP_NINE,
        NP_ZERO,
        NP_SEPARATOR,

        /* Modifier keys */
        LCTRL,
        LSHIFT,
        LALT,
        LGUI,
        RCTRL,
        RSHIFT,
        RALT,
        RGUI,

        /* Media keys */
        MUTE,
        VOLUMEUP,
        VOLUMEDOWN,
        AUDIONEXT,
        AUDIOPREV,
        AUDIOSTOP,
        AUDIOPLAY,
        AUDIOMUTE,

        /* Special keys */
        APPLICATION,
        MENU,
        BRIGHTNESSDOWN,
        BRIGHTNESSUP,
        SLEEP,
        POWER
    };

    enum class Buttons {
        LEFT,
        MIDDLE,
        RIGHT,
        SPECIAL
    };
}

#endif
