#include "Engine/Core/Renderer/Renderer.h"
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "Engine/Core/Renderer/Texture.h"
#include <iostream>

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
    // Destroy textures
    for (auto i : m_textures_list)
    {
        SDL_DestroyTexture(i.second);
    }
    m_textures_list.clear();
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

void Renderer::drawTexture(Texture* i_texture, float i_x, float i_y, float i_width, float i_height, float i_rotation)
{
    if(!i_texture){
        std::cout<<"Texture is not valid\n";
        return;
    }
    SDL_FRect rect;
    rect.x = i_x;
    rect.y = i_y;
    rect.w = i_width;
    rect.h = i_height;
    std::cout << "DrawTextureID: " << i_texture->id << "\n";
    SDL_RenderTextureRotated(m_renderer, m_textures_list[i_texture->id], nullptr, &rect, i_rotation, nullptr, SDL_FLIP_NONE);
}

void Renderer::drawLine(const SDL_FPoint* i_points, const int i_point_count)
{
    SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
    SDL_RenderLines(m_renderer, i_points, i_point_count);
}

SDL_Renderer* Renderer::getSDLRenderer() const{
    return m_renderer; 
}

bool Renderer::loadTextureFromFile(Texture* i_texture, const std::string& i_path) {
    i_texture->i_file_path = i_path;
    if(!m_renderer){
        std::cout<< "Renderer is not valid\n";
        return false;
    }
    if (!i_texture) {
        std::cout << "Texture is not valid\n";
        return false;
    }

    SDL_Texture* texture = IMG_LoadTexture(m_renderer, i_path.c_str());
    if (!texture) {
        std::cout << "Unable to load texture: " << i_path << "\n";
        return false;
    }
    size_t id = m_next_id++;
    i_texture->id = id;
    i_texture->width = texture->w;
    i_texture->height = texture->h;
    m_textures_list.emplace(id, texture);
    return true;
}

