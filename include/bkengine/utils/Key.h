#ifndef BKENGINE_KEY_H
#define BKENGINE_KEY_H

#include <string>


namespace bkengine
{
    class Key
    {
        friend class Keys;

    public:
        explicit Key();

        bool operator==(const Key &key) const;
        bool operator!=(const Key &key) const;

        operator const std::string() const;
        operator const char *() const;

        std::string toString() const;

    private:
        explicit Key(const std::string &keyString);

        std::string keyString;
    };

    class Button
    {
        friend class Buttons;

    public:
        explicit Button();

        bool operator==(const Button &button) const;
        bool operator!=(const Button &button) const;

        operator const std::string() const;
        operator const char *() const;

        std::string toString() const;

    private:
        explicit Button(const std::string &buttonString);

        std::string buttonString;
    };
}

#endif  // BKENGINE_KEY_H