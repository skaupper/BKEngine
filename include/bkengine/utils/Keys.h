#ifndef BKENGINE_KEYS_H
#define BKENGINE_KEYS_H

#include <string>

namespace bkengine
{
    /**
        Represents a keyboard key.
    */
    class Key
    {
        private:
            std::string keyString;

        public:
            /**
                Creates a instance of Key "UNKNOWN".
            */
            Key() : Key("UNKNOWN") {}

            /**
                Creates a instance of Key *keyString*.
                Valid values for *keyString* currently contain all uppercase letters,
                written-out numbers from zero to nine and a whole bunch of other keys.
                However, you should not need to call this by yourself. Instead use a predefined instance from Keys.

                \param [in] keyString A `std::string` representing a key.

                \sa Keys
            */
            Key(const std::string &keyString) : keyString(keyString) {}

            /**
                Compares two instances of Key for equality.
                Simply compares the internally stored string representation.

                \param [in] key Instance of Key to compare to.

                \return `true` if both representations are equal `false` otherwise
            */
            bool operator==(const Key &key) const;

            /**
                Compares two instances of Key for inequality.
                Simply compares the internally stored string representation.

                \param [in] key Instance of Key to compare to.

                \return `true` if the representations differ `false` otherwise
            */
            bool operator!=(const Key &key) const;

            /**
                Converts the key to a `std::string` using the stored representation.
            */
            operator const std::string() const;

            /**
                Returns the string representation of the key.

                \return The key as `std::string`.
            */
            std::string toString() const;
    };

    /**
        A collection of predefined keyboard keys.
        The string representations equal the member names as `std::string`.
    */
    class Keys
    {
        private:
            Keys() = delete;

        public:
            static Key UNKNOWN;

            /* Control Key */
            static Key RETURN;
            static Key ESCAPE;
            static Key BACKSPACE;
            static Key TAB;
            static Key SPACE;
            static Key CAPSLOCK;

            /* Number Key */
            static Key ZERO;
            static Key ONE;
            static Key TWO;
            static Key THREE;
            static Key FOUR;
            static Key FIVE;
            static Key SIX;
            static Key SEVEN;
            static Key EIGHT;
            static Key NINE;

            /* Letter Key */
            static Key A;
            static Key B;
            static Key C;
            static Key D;
            static Key E;
            static Key F;
            static Key G;
            static Key H;
            static Key I;
            static Key J;
            static Key K;
            static Key L;
            static Key M;
            static Key N;
            static Key O;
            static Key P;
            static Key Q;
            static Key R;
            static Key S;
            static Key T;
            static Key U;
            static Key V;
            static Key W;
            static Key X;
            static Key Y;
            static Key Z;

            /* Function Key */
            static Key F1;
            static Key F2;
            static Key F3;
            static Key F4;
            static Key F5;
            static Key F6;
            static Key F7;
            static Key F8;
            static Key F9;
            static Key F10;
            static Key F11;
            static Key F12;
            static Key F13;
            static Key F14;
            static Key F15;
            static Key F16;
            static Key F17;
            static Key F18;
            static Key F19;
            static Key F20;
            static Key F21;
            static Key F22;
            static Key F23;
            static Key F24;

            /* Arrow Key */
            static Key RIGHT;
            static Key LEFT;
            static Key DOWN;
            static Key UP;

            static Key PRINTSCREEN;
            static Key SCROLLLOCK;
            static Key PAUSE;
            static Key INSERT;
            static Key HOME;
            static Key PAGEUP;
            static Key DELETE;
            static Key END;
            static Key PAGEDOWN;

            /* Numpad Key */
            static Key NUMLOCKCLEAR;
            static Key NP_DIVIDE;
            static Key NP_MULTIPLY;
            static Key NP_MINUS;
            static Key NP_PLUS;
            static Key NP_ENTER;
            static Key NP_ONE;
            static Key NP_TWO;
            static Key NP_THREE;
            static Key NP_FOUR;
            static Key NP_FIVE;
            static Key NP_SIX;
            static Key NP_SEVEN;
            static Key NP_EIGHT;
            static Key NP_NINE;
            static Key NP_ZERO;
            static Key NP_SEPARATOR;

            /* Modifier Key */
            static Key LCTRL;
            static Key LSHIFT;
            static Key LALT;
            static Key LGUI;
            static Key RCTRL;
            static Key RSHIFT;
            static Key RALT;
            static Key RGUI;

            /* Media Key */
            static Key MUTE;
            static Key VOLUMEUP;
            static Key VOLUMEDOWN;
            static Key AUDIONEXT;
            static Key AUDIOPREV;
            static Key AUDIOSTOP;
            static Key AUDIOPLAY;
            static Key AUDIOMUTE;

            /* Special Key */
            static Key APPLICATION;
            static Key MENU;
            static Key BRIGHTNESSDOWN;
            static Key BRIGHTNESSUP;
            static Key SLEEP;
            static Key POWER;
    };

    /**
        Represents a mouse button.
        The string representations equal the member names as `std::string`.
    */
    class Button
    {
        private:
            std::string buttonString;

        public:
            /**
                Creates a instance of Button "UNKNOWN".
            */
            Button() : Button("UNKNOWN") {}

            /**
                Creates a instance of Button *buttonString*.
                Valid values for *buttonString* currently are "UNKNOWN", "LEFT", "RIGHT", "MIDDLE" and "SPECIAL".
                However, you should not need to call this by yourself. Instead use a predefined instance from Buttons.

                \param [in] buttonString A `std::string` representing a button.

                \sa Buttons
            */
            Button(const std::string &buttonString) : buttonString(buttonString) {}

            /**
                Compares two instances of Button for equality.
                Simply compares the internally stored string representation.

                \param [in] button Instance of Button to compare to.

                \return `true` if both representations are equal `false` otherwise
            */
            bool operator==(const Button &button) const;

            /**
                Compares two instances of Button for inequality.
                Simply compares the internally stored string representation.

                \param [in] button Instance of Button to compare to.

                \return `true` if the representations differ `false` otherwise
            */
            bool operator!=(const Button &button) const;

            /**
                Converts the button to a `std::string` using the stored representation.
            */
            operator const std::string() const;

            /**
                Returns the string representation of the button.

                \return The button as `std::string`.
            */
            std::string toString() const;
    };

    /**
        A collection of predefined mouse buttons.
    */
    class Buttons
    {
        private:
            Buttons() = delete;

        public:
            static Button UNKNOWN;
            static Button LEFT;
            static Button RIGHT;
            static Button MIDDLE;
            static Button SPECIAL;
    };
}

#endif
