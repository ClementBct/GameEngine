#pragma once
#include <string>
#include <unordered_map>

struct SDL_Texture;

class RessourceLoader
{
public :
	RessourceLoader(class Renderer& i_renderer);
	~RessourceLoader();
	SDL_Texture* loadTexture(const std::string& i_file_path);

private :
	class Renderer& m_renderer;
	std::unordered_map<std::string, SDL_Texture*> m_textures_list;
};

