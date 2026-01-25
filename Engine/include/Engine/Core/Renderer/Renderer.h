#pragma once

#include <string>
#include <unordered_map>

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_FRect;
struct SDL_Window;
struct SDL_FPoint;

class Renderer
{
public:
	Renderer();
	~Renderer();
	SDL_Renderer* createRenderer(SDL_Window* i_window);

    void beginFrame();

    void endFrame();
	void drawTexture(class Texture* i_texture,float i_x, float i_y, float i_width, float i_height, float i_rotation);
	void drawLine(const SDL_FPoint* i_points,const int i_point_count);
    SDL_Renderer* getSDLRenderer() const;
	bool loadTextureFromFile(Texture* i_texture, const std::string& i_path);
protected:
private:
	std::unordered_map<size_t, SDL_Texture*> m_textures_list;
	SDL_Renderer* m_renderer = nullptr;
	size_t m_next_id = 0;
};

