#pragma once
#include "Component.h"

struct SDL_Texture;

class SpriteComponent : public Component
{
public:
	SpriteComponent(class GameObject& i_owner);
	void setTexture(SDL_Texture* i_texture);
	SDL_Texture* getTexture() const;
	int getZOrder();
	Vector2D getWorldSize();
protected:
private:
	float m_texture_h = -1.0f;
	float m_texture_w = -1.0f;
	Vector2D m_world_size;
	int m_local_z_order = 0;
	std::string m_texture_path = "";
	SDL_Texture* m_texture = nullptr;
};

