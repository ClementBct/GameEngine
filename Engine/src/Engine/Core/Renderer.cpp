#include "Engine/Core/Renderer.h"
#include "SDL3/SDL.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_renderer);
}

SDL_Renderer* Renderer::createRenderer(SDL_Window* i_window)
{
    m_renderer = SDL_CreateRenderer(i_window, nullptr);
    if (!m_renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
    }
    return m_renderer;

}

void Renderer::beginFrame() {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}

void Renderer::endFrame() {
    SDL_RenderPresent(m_renderer);
}

void Renderer::drawTexture(SDL_Texture* i_texture, SDL_FRect* i_rect, float i_rotation)
{
    SDL_RenderTextureRotated(m_renderer, i_texture,nullptr, i_rect, i_rotation,nullptr,SDL_FLIP_NONE);
}

void Renderer::drawLine(const SDL_FPoint* i_points, const int i_point_count)
{
    SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
    SDL_RenderLines(m_renderer, i_points, i_point_count);
}

SDL_Renderer* Renderer::getSDLRenderer() const{
    return m_renderer; 
}
