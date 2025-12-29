#include "Engine/Core/RessourceLoader.h"
#include <SDL3_image/SDL_image.h>
#include <print>
#include "Engine/Core/Renderer.h"

RessourceLoader::RessourceLoader(Renderer& i_renderer) : m_renderer(i_renderer)
{
}

RessourceLoader::~RessourceLoader()
{
    // Destroy textures
    for (auto i : m_textures_list)
    {
        SDL_DestroyTexture(i.second);
    }
    m_textures_list.clear();
}

SDL_Texture* RessourceLoader::loadTexture(const std::string& i_file_path)
{
    SDL_Renderer* renderer = m_renderer.getSDLRenderer();
    if (!renderer) {
        std::println("Enable to load texture: renderer is not valid");
        return nullptr;
    }
    auto iter = m_textures_list.find(i_file_path);
    if (iter != m_textures_list.end()) {
        //Texture trouvé dans la map
        return iter->second;
    }
    //Création de la textures car pas trouvé dans la map
    SDL_Texture* texture;
    texture = IMG_LoadTexture(renderer, i_file_path.c_str());
    if (texture) {
        m_textures_list.emplace(i_file_path.c_str(), texture);
        return texture;
    }
    else {
        std::println("Enable to load texture");
        return nullptr;
    }
}
