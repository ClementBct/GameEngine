#include "Engine/System/Input/InputSystem.h"
#include "Engine/Utils/Math.h"

#include "Engine/ECS/GameObject.h"
#include "Engine/Core/Scene.h"
#include "SDL3/SDL.h"

//tempo
#include <print>

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::onUpdate(double i_dt_s) {
    (void)i_dt_s;
    SDL_Event event;
    // While there are still events in the queue...
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            // If event is SDL_QUIT exit.
        case SDL_EVENT_QUIT:
            m_quit_callback();
            break;
        case SDL_EVENT_KEY_DOWN: // touche appuyée
            m_key_states[event.key.key] = true;
            break;
        case SDL_EVENT_KEY_UP: // touche relâchée
            m_key_states[event.key.key] = false;
        case SDL_EVENT_MOUSE_MOTION:
            m_mouse_screen_position.x = event.motion.x;
            m_mouse_screen_position.y = event.motion.y;
        default:
            break;
        }
    }
}

void InputSystem::registerQuitCallback(std::function<void()> i_callback)
{
    m_quit_callback = i_callback;
}

bool InputSystem::isKeyPressed(const SDL_Keycode i_key) const {
    auto it = m_key_states.find(i_key);
    return it != m_key_states.end() && it->second;
}

Vector2D InputSystem::getMouseScreenPosition() {
    return m_mouse_screen_position;
}

EKeyboardKey InputSystem::sdlKeyToKeyBoardKey(const SDL_Keycode i_key) {
    switch (i_key)
    {
        // Lettres
    case SDLK_A: return EKeyboardKey::A;
    case SDLK_B: return EKeyboardKey::B;
    case SDLK_C: return EKeyboardKey::C;
    case SDLK_D: return EKeyboardKey::D;
    case SDLK_E: return EKeyboardKey::E;
    case SDLK_F: return EKeyboardKey::F;
    case SDLK_G: return EKeyboardKey::G;
    case SDLK_H: return EKeyboardKey::H;
    case SDLK_I: return EKeyboardKey::I;
    case SDLK_J: return EKeyboardKey::J;
    case SDLK_K: return EKeyboardKey::K;
    case SDLK_L: return EKeyboardKey::L;
    case SDLK_M: return EKeyboardKey::M;
    case SDLK_N: return EKeyboardKey::N;
    case SDLK_O: return EKeyboardKey::O;
    case SDLK_P: return EKeyboardKey::P;
    case SDLK_Q: return EKeyboardKey::Q;
    case SDLK_R: return EKeyboardKey::R;
    case SDLK_S: return EKeyboardKey::S;
    case SDLK_T: return EKeyboardKey::T;
    case SDLK_U: return EKeyboardKey::U;
    case SDLK_V: return EKeyboardKey::V;
    case SDLK_W: return EKeyboardKey::W;
    case SDLK_X: return EKeyboardKey::X;
    case SDLK_Y: return EKeyboardKey::Y;
    case SDLK_Z: return EKeyboardKey::Z;

        // Chiffres (ligne du haut)
    case SDLK_0: return EKeyboardKey::Num0;
    case SDLK_1: return EKeyboardKey::Num1;
    case SDLK_2: return EKeyboardKey::Num2;
    case SDLK_3: return EKeyboardKey::Num3;
    case SDLK_4: return EKeyboardKey::Num4;
    case SDLK_5: return EKeyboardKey::Num5;
    case SDLK_6: return EKeyboardKey::Num6;
    case SDLK_7: return EKeyboardKey::Num7;
    case SDLK_8: return EKeyboardKey::Num8;
    case SDLK_9: return EKeyboardKey::Num9;

        // Touches de fonction
    case SDLK_F1:  return EKeyboardKey::F1;
    case SDLK_F2:  return EKeyboardKey::F2;
    case SDLK_F3:  return EKeyboardKey::F3;
    case SDLK_F4:  return EKeyboardKey::F4;
    case SDLK_F5:  return EKeyboardKey::F5;
    case SDLK_F6:  return EKeyboardKey::F6;
    case SDLK_F7:  return EKeyboardKey::F7;
    case SDLK_F8:  return EKeyboardKey::F8;
    case SDLK_F9:  return EKeyboardKey::F9;
    case SDLK_F10: return EKeyboardKey::F10;
    case SDLK_F11: return EKeyboardKey::F11;
    case SDLK_F12: return EKeyboardKey::F12;

        // Contrôle
    case SDLK_ESCAPE:      return EKeyboardKey::Escape;
    case SDLK_TAB:         return EKeyboardKey::Tab;
    case SDLK_CAPSLOCK:    return EKeyboardKey::CapsLock;
    case SDLK_LSHIFT:      return EKeyboardKey::LeftShift;
    case SDLK_RSHIFT:      return EKeyboardKey::RightShift;
    case SDLK_LCTRL:       return EKeyboardKey::LeftControl;
    case SDLK_RCTRL:       return EKeyboardKey::RightControl;
    case SDLK_LALT:        return EKeyboardKey::LeftAlt;
    case SDLK_RALT:        return EKeyboardKey::RightAlt;
    case SDLK_LGUI:        return EKeyboardKey::LeftSuper;
    case SDLK_RGUI:        return EKeyboardKey::RightSuper;
    case SDLK_RETURN:      return EKeyboardKey::Enter;
    case SDLK_BACKSPACE:   return EKeyboardKey::Backspace;
    case SDLK_SPACE:       return EKeyboardKey::Space;

        // Flèches
    case SDLK_UP:    return EKeyboardKey::ArrowUp;
    case SDLK_DOWN:  return EKeyboardKey::ArrowDown;
    case SDLK_LEFT:  return EKeyboardKey::ArrowLeft;
    case SDLK_RIGHT: return EKeyboardKey::ArrowRight;

        // Navigation
    case SDLK_INSERT:    return EKeyboardKey::Insert;
    case SDLK_DELETE:    return EKeyboardKey::Delete;
    case SDLK_HOME:      return EKeyboardKey::Home;
    case SDLK_END:       return EKeyboardKey::End;
    case SDLK_PAGEUP:    return EKeyboardKey::PageUp;
    case SDLK_PAGEDOWN:  return EKeyboardKey::PageDown;

        // Pavé numérique
    case SDLK_KP_0:        return EKeyboardKey::Numpad0;
    case SDLK_KP_1:        return EKeyboardKey::Numpad1;
    case SDLK_KP_2:        return EKeyboardKey::Numpad2;
    case SDLK_KP_3:        return EKeyboardKey::Numpad3;
    case SDLK_KP_4:        return EKeyboardKey::Numpad4;
    case SDLK_KP_5:        return EKeyboardKey::Numpad5;
    case SDLK_KP_6:        return EKeyboardKey::Numpad6;
    case SDLK_KP_7:        return EKeyboardKey::Numpad7;
    case SDLK_KP_8:        return EKeyboardKey::Numpad8;
    case SDLK_KP_9:        return EKeyboardKey::Numpad9;
    case SDLK_KP_PLUS:     return EKeyboardKey::NumpadAdd;
    case SDLK_KP_MINUS:    return EKeyboardKey::NumpadSubtract;
    case SDLK_KP_MULTIPLY: return EKeyboardKey::NumpadMultiply;
    case SDLK_KP_DIVIDE:   return EKeyboardKey::NumpadDivide;
    case SDLK_KP_ENTER:    return EKeyboardKey::NumpadEnter;
    case SDLK_KP_DECIMAL:  return EKeyboardKey::NumpadDecimal;

        // Symboles
    case SDLK_MINUS:        return EKeyboardKey::Minus;
    case SDLK_EQUALS:       return EKeyboardKey::Equals;
    case SDLK_LEFTBRACKET:  return EKeyboardKey::LeftBracket;
    case SDLK_RIGHTBRACKET: return EKeyboardKey::RightBracket;
    case SDLK_BACKSLASH:    return EKeyboardKey::Backslash;
    case SDLK_SEMICOLON:    return EKeyboardKey::Semicolon;
    case SDLK_APOSTROPHE:   return EKeyboardKey::Apostrophe;
    case SDLK_GRAVE:        return EKeyboardKey::GraveAccent;
    case SDLK_COMMA:        return EKeyboardKey::Comma;
    case SDLK_PERIOD:       return EKeyboardKey::Period;
    case SDLK_SLASH:        return EKeyboardKey::Slash;

        // Verrous / système
    case SDLK_NUMLOCKCLEAR: return EKeyboardKey::NumLock;
    case SDLK_SCROLLLOCK:   return EKeyboardKey::ScrollLock;
    case SDLK_PRINTSCREEN:  return EKeyboardKey::PrintScreen;
    case SDLK_PAUSE:        return EKeyboardKey::Pause;

    default:
        return EKeyboardKey::Unknown;
    }
}
