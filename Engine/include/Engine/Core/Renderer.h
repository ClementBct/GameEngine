#pragma once

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
	void drawTexture(SDL_Texture* i_texture, SDL_FRect* i_rect, float i_rotation);
	void drawLine(const SDL_FPoint* i_points,const int i_point_count);
    SDL_Renderer* getSDLRenderer() const;
protected:
private:
	SDL_Renderer* m_renderer = nullptr;
};

