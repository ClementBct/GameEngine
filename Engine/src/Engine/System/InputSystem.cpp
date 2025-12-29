#include "Engine/System/InputSystem.h"

#include "Engine/ECS/GameObject.h"
#include "Engine/Core/Scene.h"
#include "SDL3/SDL.h"

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::processInput(Scene* i_scene)
{
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
            for (auto game_object : i_scene->getGameObjectList()) {
                if (game_object->m_is_keyboardEventEnable) {
                    game_object->onKeyPressed(event.key.key);
                }
            }
            break;
        case SDL_EVENT_KEY_UP: // touche relâchée
            m_key_states[event.key.key] = false;
            for (auto game_object : i_scene->getGameObjectList()) {
                if (game_object->m_is_keyboardEventEnable) {
                    game_object->onKeyReleased(event.key.key);
                }
            }
        default:
            break;
        }
    }
}

void InputSystem::registerQuitCallback(std::function<void()> i_callback)
{
    m_quit_callback = i_callback;
}

bool InputSystem::isKeyPressed(SDL_Keycode i_key) const {
    auto it = m_key_states.find(i_key);
    return it != m_key_states.end() && it->second;
}
