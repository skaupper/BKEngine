#include "Keys.h"

using namespace bkengine;

Keys Keys::UNKNOWN("UNKNOWN");

/* Control keys */
Keys Keys::RETURN("RETURN");
Keys Keys::ESCAPE("ESCAPE");
Keys Keys::BACKSPACE("BACKSPACE");
Keys Keys::TAB("TAB");
Keys Keys::SPACE("SPACE");
Keys Keys::CAPSLOCK("CAPSLOCK");

/* Number keys */
Keys Keys::ZERO("ZERO");
Keys Keys::ONE("ONE");
Keys Keys::TWO("TWO");
Keys Keys::THREE("THREE");
Keys Keys::FOUR("FOUR");
Keys Keys::FIVE("FIVE");
Keys Keys::SIX("SIX");
Keys Keys::SEVEN("SEVEN");
Keys Keys::EIGHT("EIGHT");
Keys Keys::NINE("NINE");

/* Letter keys */
Keys Keys::A("A");
Keys Keys::B("B");
Keys Keys::C("C");
Keys Keys::D("D");
Keys Keys::E("E");
Keys Keys::F("F");
Keys Keys::G("G");
Keys Keys::H("H");
Keys Keys::I("I");
Keys Keys::J("J");
Keys Keys::K("K");
Keys Keys::L("L");
Keys Keys::M("M");
Keys Keys::N("N");
Keys Keys::O("O");
Keys Keys::P("P");
Keys Keys::Q("Q");
Keys Keys::R("R");
Keys Keys::S("S");
Keys Keys::T("T");
Keys Keys::U("U");
Keys Keys::V("V");
Keys Keys::W("W");
Keys Keys::X("X");
Keys Keys::Y("Y");
Keys Keys::Z("Z");

/* Function keys */
Keys Keys::F1("F1");
Keys Keys::F2("F2");
Keys Keys::F3("F3");
Keys Keys::F4("F4");
Keys Keys::F5("F5");
Keys Keys::F6("F6");
Keys Keys::F7("F7");
Keys Keys::F8("F8");
Keys Keys::F9("F9");
Keys Keys::F10("F10");
Keys Keys::F11("F11");
Keys Keys::F12("F12");
Keys Keys::F13("F13");
Keys Keys::F14("F14");
Keys Keys::F15("F15");
Keys Keys::F16("F16");
Keys Keys::F17("F17");
Keys Keys::F18("F18");
Keys Keys::F19("F19");
Keys Keys::F20("F20");
Keys Keys::F21("F21");
Keys Keys::F22("F22");
Keys Keys::F23("F23");
Keys Keys::F24("F24");

/* Arrow keys */
Keys Keys::RIGHT("RIGHT");
Keys Keys::LEFT("LEFT");
Keys Keys::DOWN("DOWN");
Keys Keys::UP("UP");

Keys Keys::PRINTSCREEN("PRINTSCREEN");
Keys Keys::SCROLLLOCK("SCROLLLOCK");
Keys Keys::PAUSE("PAUSE");
Keys Keys::INSERT("INSERT");
Keys Keys::HOME("HOME");
Keys Keys::PAGEUP("PAGEUP");
Keys Keys::DELETE("DELETE");
Keys Keys::END("END");
Keys Keys::PAGEDOWN("PAGEDOWN");

/* Numpad keys */
Keys Keys::NUMLOCKCLEAR("NUMLOCKCLEAR");
Keys Keys::NP_DIVIDE("NP_DIVIDE");
Keys Keys::NP_MULTIPLY("NP_MULTIPLY");
Keys Keys::NP_MINUS("NP_MINUS");
Keys Keys::NP_PLUS("NP_PLUS");
Keys Keys::NP_ENTER("NP_ENTER");
Keys Keys::NP_ONE("NP_ONE");
Keys Keys::NP_TWO("NP_TWO");
Keys Keys::NP_THREE("NP_THREE");
Keys Keys::NP_FOUR("NP_FOUR");
Keys Keys::NP_FIVE("NP_FIVE");
Keys Keys::NP_SIX("NP_SIX");
Keys Keys::NP_SEVEN("NP_SEVEN");
Keys Keys::NP_EIGHT("NP_EIGHT");
Keys Keys::NP_NINE("NP_NINE");
Keys Keys::NP_ZERO("NP_ZERO");
Keys Keys::NP_SEPARATOR("NP_SEPARATOR");

/* Modifier keys */
Keys Keys::LCTRL("LCTRL");
Keys Keys::LSHIFT("LSHIFT");
Keys Keys::LALT("LALT");
Keys Keys::LGUI("LGUI");
Keys Keys::RCTRL("RCTRL");
Keys Keys::RSHIFT("RSHIFT");
Keys Keys::RALT("RALT");
Keys Keys::RGUI("RGUI");

/* Media keys */
Keys Keys::MUTE("MUTE");
Keys Keys::VOLUMEUP("VOLUMEUP");
Keys Keys::VOLUMEDOWN("VOLUMEDOWN");
Keys Keys::AUDIONEXT("AUDIONEXT");
Keys Keys::AUDIOPREV("AUDIOPREV");
Keys Keys::AUDIOSTOP("AUDIOSTOP");
Keys Keys::AUDIOPLAY("AUDIOPLAY");
Keys Keys::AUDIOMUTE("AUDIOMUTE");

/* Special keys */
Keys Keys::APPLICATION("APPLICATION");
Keys Keys::MENU("MENU");
Keys Keys::BRIGHTNESSDOWN("BRIGHTNESSDOWN");
Keys Keys::BRIGHTNESSUP("BRIGHTNESSUP");
Keys Keys::SLEEP("SLEEP");
Keys Keys::POWER("POWER");

bool Keys::operator==(const Keys &key) const
{
    return keyString == key.keyString;
}

bool Keys::operator!=(const Keys &key) const
{
    return !(key == *this);
}

Keys::operator const std::string() const
{
    return keyString;
}

Keys::operator const char *() const
{
    return keyString.c_str();
}

std::string Keys::toString() const
{
    return keyString;
}


Buttons Buttons::UNKNOWN("UNKNOWN");
Buttons Buttons::LEFT("LEFT");
Buttons Buttons::RIGHT("RIGHT");
Buttons Buttons::MIDDLE("MIDDLE");
Buttons Buttons::SPECIAL("SPECIAL");

bool Buttons::operator==(const Buttons &button) const
{
    return buttonString == button.buttonString;
}

bool Buttons::operator!=(const Buttons &button) const
{
    return !(button == *this);
}

Buttons::operator const std::string() const
{
    return buttonString;
}

Buttons::operator const char *() const
{
    return buttonString.c_str();
}

std::string Buttons::toString()
{
    return buttonString;
}
