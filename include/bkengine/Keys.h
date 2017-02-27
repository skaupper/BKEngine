#ifndef KEYS_H
#define KEYS_H

#include <string>

namespace bkengine
{
    class Keys
    {
        private:
            std::string keyString;

        public:
            Keys() : Keys("UNKNOWN") {}
            Keys(const std::string &keyString) : keyString(keyString) {}
            bool operator==(const Keys &) const;
            bool operator!=(const Keys &) const;
            std::string toString() const;

            static Keys UNKNOWN;

            /* Control keys */
            static Keys RETURN;
            static Keys ESCAPE;
            static Keys BACKSPACE;
            static Keys TAB;
            static Keys SPACE;
            static Keys CAPSLOCK;

            /* Number keys */
            static Keys ZERO;
            static Keys ONE;
            static Keys TWO;
            static Keys THREE;
            static Keys FOUR;
            static Keys FIVE;
            static Keys SIX;
            static Keys SEVEN;
            static Keys EIGHT;
            static Keys NINE;

            /* Letter keys */
            static Keys A;
            static Keys B;
            static Keys C;
            static Keys D;
            static Keys E;
            static Keys F;
            static Keys G;
            static Keys H;
            static Keys I;
            static Keys J;
            static Keys K;
            static Keys L;
            static Keys M;
            static Keys N;
            static Keys O;
            static Keys P;
            static Keys Q;
            static Keys R;
            static Keys S;
            static Keys T;
            static Keys U;
            static Keys V;
            static Keys W;
            static Keys X;
            static Keys Y;
            static Keys Z;

            /* Function keys */
            static Keys F1;
            static Keys F2;
            static Keys F3;
            static Keys F4;
            static Keys F5;
            static Keys F6;
            static Keys F7;
            static Keys F8;
            static Keys F9;
            static Keys F10;
            static Keys F11;
            static Keys F12;
            static Keys F13;
            static Keys F14;
            static Keys F15;
            static Keys F16;
            static Keys F17;
            static Keys F18;
            static Keys F19;
            static Keys F20;
            static Keys F21;
            static Keys F22;
            static Keys F23;
            static Keys F24;

            /* Arrow keys */
            static Keys RIGHT;
            static Keys LEFT;
            static Keys DOWN;
            static Keys UP;

            static Keys PRINTSCREEN;
            static Keys SCROLLLOCK;
            static Keys PAUSE;
            static Keys INSERT;
            static Keys HOME;
            static Keys PAGEUP;
            static Keys DELETE;
            static Keys END;
            static Keys PAGEDOWN;

            /* Numpad keys */
            static Keys NUMLOCKCLEAR;
            static Keys NP_DIVIDE;
            static Keys NP_MULTIPLY;
            static Keys NP_MINUS;
            static Keys NP_PLUS;
            static Keys NP_ENTER;
            static Keys NP_ONE;
            static Keys NP_TWO;
            static Keys NP_THREE;
            static Keys NP_FOUR;
            static Keys NP_FIVE;
            static Keys NP_SIX;
            static Keys NP_SEVEN;
            static Keys NP_EIGHT;
            static Keys NP_NINE;
            static Keys NP_ZERO;
            static Keys NP_SEPARATOR;

            /* Modifier keys */
            static Keys LCTRL;
            static Keys LSHIFT;
            static Keys LALT;
            static Keys LGUI;
            static Keys RCTRL;
            static Keys RSHIFT;
            static Keys RALT;
            static Keys RGUI;

            /* Media keys */
            static Keys MUTE;
            static Keys VOLUMEUP;
            static Keys VOLUMEDOWN;
            static Keys AUDIONEXT;
            static Keys AUDIOPREV;
            static Keys AUDIOSTOP;
            static Keys AUDIOPLAY;
            static Keys AUDIOMUTE;

            /* Special keys */
            static Keys APPLICATION;
            static Keys MENU;
            static Keys BRIGHTNESSDOWN;
            static Keys BRIGHTNESSUP;
            static Keys SLEEP;
            static Keys POWER;
    };

    class Buttons
    {
        private:
            std::string buttonString;

        public:
            Buttons() : Buttons("UNKNOWN") {}
            Buttons(const std::string &buttonString) : buttonString(buttonString) {}
            bool operator==(const Buttons &) const;
            bool operator!=(const Buttons &) const;
            std::string toString();

            static Buttons UNKNOWN;
            static Buttons LEFT;
            static Buttons RIGHT;
            static Buttons MIDDLE;
            static Buttons SPECIAL;
    };
}

#endif
