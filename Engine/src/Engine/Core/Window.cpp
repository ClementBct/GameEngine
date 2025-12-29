#include "Engine/Core/Window.h"

#include "SDL3/SDL.h"
#include <print>

Window::Window()
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }
    m_window = SDL_CreateWindow(m_window_name.c_str(), m_screen_width, m_screen_height, 0);
    if (!m_window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
    }
}

Window::~Window()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

SDL_Window* Window::getWindow()
{
    return m_window;
}

int Window::getWindowHeight()
{
    return m_screen_height;
}

int Window::getWindowWidth()
{
    return m_screen_width;
}
