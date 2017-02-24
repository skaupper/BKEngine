#include "SDLEventInterface.h"

using namespace bkengine;

static Keys mapSDLKeys(SDL_Keycode code)
{
    static std::map<SDL_Keycode, Keys> map = {
        { SDLK_RETURN, Keys::RETURN },
        { SDLK_ESCAPE, Keys::ESCAPE },
        { SDLK_BACKSPACE, Keys::BACKSPACE },
        { SDLK_TAB, Keys::TAB },
        { SDLK_SPACE, Keys::SPACE },
        { SDLK_CAPSLOCK, Keys::CAPSLOCK },

        { SDLK_0, Keys::ZERO },
        { SDLK_1, Keys::ONE },
        { SDLK_2, Keys::TWO },
        { SDLK_3, Keys::THREE },
        { SDLK_4, Keys::FOUR },
        { SDLK_5, Keys::FIVE },
        { SDLK_6, Keys::SIX },
        { SDLK_7, Keys::SEVEN },
        { SDLK_8, Keys::EIGHT },
        { SDLK_9, Keys::NINE },

        { SDLK_a, Keys::A },
        { SDLK_b, Keys::B },
        { SDLK_c, Keys::C },
        { SDLK_d, Keys::D },
        { SDLK_e, Keys::E },
        { SDLK_f, Keys::F },
        { SDLK_g, Keys::G },
        { SDLK_h, Keys::H },
        { SDLK_i, Keys::I },
        { SDLK_j, Keys::J },
        { SDLK_k, Keys::K },
        { SDLK_l, Keys::L },
        { SDLK_m, Keys::M },
        { SDLK_n, Keys::N },
        { SDLK_o, Keys::O },
        { SDLK_p, Keys::P },
        { SDLK_q, Keys::Q },
        { SDLK_r, Keys::R },
        { SDLK_s, Keys::S },
        { SDLK_t, Keys::T },
        { SDLK_u, Keys::U },
        { SDLK_v, Keys::V },
        { SDLK_w, Keys::W },
        { SDLK_x, Keys::X },
        { SDLK_y, Keys::Y },
        { SDLK_z, Keys::Z },

        { SDLK_F1, Keys::F1 },
        { SDLK_F2, Keys::F2 },
        { SDLK_F3, Keys::F3 },
        { SDLK_F4, Keys::F4 },
        { SDLK_F5, Keys::F5 },
        { SDLK_F6, Keys::F6 },
        { SDLK_F7, Keys::F7 },
        { SDLK_F8, Keys::F8 },
        { SDLK_F9, Keys::F9 },
        { SDLK_F10, Keys::F10 },
        { SDLK_F11, Keys::F11 },
        { SDLK_F12, Keys::F12 },
        { SDLK_F13, Keys::F13 },
        { SDLK_F14, Keys::F14 },
        { SDLK_F15, Keys::F15 },
        { SDLK_F16, Keys::F16 },
        { SDLK_F17, Keys::F17 },
        { SDLK_F18, Keys::F18 },
        { SDLK_F19, Keys::F19 },
        { SDLK_F20, Keys::F20 },
        { SDLK_F21, Keys::F21 },
        { SDLK_F22, Keys::F22 },
        { SDLK_F23, Keys::F23 },
        { SDLK_F24, Keys::F24 },

        { SDLK_RIGHT, Keys::RIGHT },
        { SDLK_LEFT, Keys::LEFT },
        { SDLK_DOWN, Keys::DOWN },
        { SDLK_UP, Keys::UP },

        { SDLK_PRINTSCREEN, Keys::PRINTSCREEN },
        { SDLK_SCROLLLOCK, Keys::SCROLLLOCK },
        { SDLK_PAUSE, Keys::PAUSE },
        { SDLK_INSERT, Keys::INSERT },
        { SDLK_HOME, Keys::HOME },
        { SDLK_PAGEUP, Keys::PAGEUP },
        { SDLK_DELETE, Keys::DELETE },
        { SDLK_END, Keys::END },
        { SDLK_PAGEDOWN, Keys::PAGEDOWN },

        { SDLK_NUMLOCKCLEAR, Keys::NUMLOCKCLEAR },
        { SDLK_KP_DIVIDE, Keys::NP_DIVIDE },
        { SDLK_KP_MULTIPLY, Keys::NP_MULTIPLY },
        { SDLK_KP_MINUS, Keys::NP_MINUS },
        { SDLK_KP_PLUS, Keys::NP_PLUS },
        { SDLK_KP_ENTER, Keys::NP_ENTER },
        { SDLK_KP_1, Keys::NP_ONE },
        { SDLK_KP_2, Keys::NP_TWO },
        { SDLK_KP_3, Keys::NP_THREE },
        { SDLK_KP_4, Keys::NP_FOUR },
        { SDLK_KP_5, Keys::NP_FIVE },
        { SDLK_KP_6, Keys::NP_SIX },
        { SDLK_KP_7, Keys::NP_SEVEN },
        { SDLK_KP_8, Keys::NP_EIGHT },
        { SDLK_KP_9, Keys::NP_NINE },
        { SDLK_KP_0, Keys::NP_ZERO },
        { SDLK_KP_PERIOD, Keys::NP_SEPARATOR },
        { SDLK_KP_COMMA, Keys::NP_SEPARATOR },

        { SDLK_LCTRL, Keys::LCTRL },
        { SDLK_LSHIFT, Keys::LSHIFT },
        { SDLK_LALT, Keys::LALT },
        { SDLK_LGUI, Keys::LGUI },
        { SDLK_RCTRL, Keys::RCTRL },
        { SDLK_RSHIFT, Keys::RSHIFT },
        { SDLK_RALT, Keys::RALT },
        { SDLK_RGUI, Keys::RGUI },

        { SDLK_MUTE, Keys::MUTE },
        { SDLK_VOLUMEUP, Keys::VOLUMEUP },
        { SDLK_VOLUMEDOWN, Keys::VOLUMEDOWN },
        { SDLK_AUDIONEXT, Keys::AUDIONEXT },
        { SDLK_AUDIOPREV, Keys::AUDIOPREV },
        { SDLK_AUDIOSTOP, Keys::AUDIOSTOP },
        { SDLK_AUDIOPLAY, Keys::AUDIOPLAY },
        { SDLK_AUDIOMUTE, Keys::AUDIOMUTE },

        { SDLK_APPLICATION, Keys::APPLICATION },
        { SDLK_MENU, Keys::MENU },
        { SDLK_BRIGHTNESSDOWN, Keys::BRIGHTNESSDOWN },
        { SDLK_BRIGHTNESSUP, Keys::BRIGHTNESSUP },
        { SDLK_SLEEP, Keys::SLEEP },
        { SDLK_POWER, Keys::POWER }
    };

    if (map.find(code) != map.end()) {
        return map[code];
    } else {
        return Keys::UNKNOWN;
    }
}

bool SDLEventInterface::ready()
{
    return (MANGLE_SDL(SDL_PollEvent)(nullptr) != 0);
}

Event SDLEventInterface::poll()
{
    SDL_Event event;

    if (MANGLE_SDL(SDL_PollEvent)(&event) == 0) {
        Logger::LogWarning("SDLEventInterface::poll(): No event to poll. Use ready() to check if one is available");
        return Event();
    }

    Event e;

    switch (event.type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
            KeyboardEvent keyboardEvent;
            e.type = EventType::KEYBOARD;
            e.windowId = event.key.windowID;
            keyboardEvent.key = mapSDLKeys(event.key.keysym.sym);
            keyboardEvent.state = (event.type == SDL_KEYDOWN ? KeyState::DOWN :
                                   KeyState::UP);
            keyboardEvent.repeat = (event.key.repeat != 0);
            e.keyboard = keyboardEvent;
            break;
        }

        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        {
            MouseEvent mouseEvent;
            e.type = EventType::MOUSE;
            e.windowId = event.button.windowID;

            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    mouseEvent.button = Buttons::LEFT;
                    break;

                case SDL_BUTTON_RIGHT:
                    mouseEvent.button = Buttons::RIGHT;
                    break;

                case SDL_BUTTON_MIDDLE:
                    mouseEvent.button = Buttons::MIDDLE;
                    break;

                case SDL_BUTTON_X1:
                case SDL_BUTTON_X2:
                    mouseEvent.button = Buttons::SPECIAL;
                    mouseEvent.specialId = (event.button.button == SDL_BUTTON_X1 ? 1 : 2);
                    break;
            }

            mouseEvent.x = event.button.x;
            mouseEvent.y = event.button.y;
            mouseEvent.clicks = event.button.clicks;
            mouseEvent.state = (event.type == SDL_MOUSEBUTTONDOWN ? ButtonState::DOWN :
                                ButtonState::UP);
            e.mouse = mouseEvent;
            break;
        }

        case SDL_MOUSEMOTION:
        {
            MotionEvent motionEvent;
            e.type = EventType::MOTION;
            e.windowId = event.motion.windowID;
            motionEvent.x = event.motion.x;
            motionEvent.y = event.motion.y;
            motionEvent.relativeX = event.motion.xrel;
            motionEvent.relativeY = event.motion.yrel;
            e.motion = motionEvent;
            break;
        }

        case SDL_MOUSEWHEEL:
        {
            WheelEvent wheelEvent;
            e.type = EventType::WHEEL;
            e.windowId = event.motion.windowID;
            wheelEvent.x = event.wheel.x;
            wheelEvent.y = event.wheel.y;
            wheelEvent.direction = (event.wheel.direction == SDL_MOUSEWHEEL_NORMAL ?
                                    WheelDirection::NORMAL : WheelDirection::FLIPPED);
            e.wheel = wheelEvent;
            break;
        }

        case SDL_QUIT:
        {
            e.type = EventType::QUIT;
            break;
        }

        default:
        {
            e.type = EventType::UNKNOWN;
            /* This one would spam a lot! */
            // Logger::LogDebug("SDLEventInterface::poll(): SDL event " + std::to_string(event.type) + " occurred which is not mapped by the interface");
            break;
        }
    }

    return e;
}
