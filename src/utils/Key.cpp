#include "utils/Key.h"

using namespace bkengine;


Key::Key() : Key("UNKNOWN")
{
}

Key::Key(const std::string &keyString) : keyString(keyString)
{
}

bool Key::operator==(const Key &key) const
{
    return keyString == key.keyString;
}

bool Key::operator!=(const Key &key) const
{
    return !(key == *this);
}

Key::operator const std::string() const
{
    return keyString;
}

Key::operator const char *() const
{
    return keyString.c_str();
}

std::string Key::toString() const
{
    return keyString;
}


Button::Button() : Button("UNKNOWN")
{
}

Button::Button(const std::string &buttonString) : buttonString(buttonString)
{
}

bool Button::operator==(const Button &button) const
{
    return buttonString == button.buttonString;
}

bool Button::operator!=(const Button &button) const
{
    return !(button == *this);
}

Button::operator const std::string() const
{
    return buttonString;
}

Button::operator const char *() const
{
    return buttonString.c_str();
}

std::string Button::toString() const
{
    return buttonString;
}