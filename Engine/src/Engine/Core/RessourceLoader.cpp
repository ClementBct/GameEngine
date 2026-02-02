#include "Engine/Core/RessourceLoader.h"
#include <SDL3_image/SDL_image.h>
#include "Engine/Core/Renderer/Renderer.h"
#include "Engine/Core/Renderer/Texture.h"
#include <iostream>

RessourceLoader::RessourceLoader(Renderer& i_renderer) : m_renderer(i_renderer)
{
}

RessourceLoader::~RessourceLoader()
{
}

Texture* RessourceLoader::createTexture(const std::string& i_file_path)
{
    //ça ne crée pas vraiment la texture car on verifie qu'elle n'est pas deja chargé avant
    std::string final_path = TEXTURE_PATH + i_file_path;
    // Check if texture is already loaded in memory
    auto iter = m_textures_list.find(final_path);
    if (iter != m_textures_list.end()) {
        return iter->second; // retourne texture
    }
    std::cout << "New texture created: " << final_path << "\n";
    Texture* new_texture = new Texture();
    if(!m_renderer.loadTextureFromFile(new_texture, final_path)){
        return nullptr;
    }

    // Stocke dans la map
    m_textures_list.emplace(i_file_path, new_texture);

    // Retourne le pointeur
    return new_texture;
}
