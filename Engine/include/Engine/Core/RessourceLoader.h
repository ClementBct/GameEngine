#pragma once
#include <string>
#include <unordered_map>
#include <memory>

class RessourceLoader
{
public :
	RessourceLoader(class Renderer& i_renderer);
	~RessourceLoader();
	class Texture* createTexture(const std::string& i_file_path);

private :
	class Renderer& m_renderer;
	std::unordered_map<std::string, class Texture*> m_textures_list;
};

