#pragma once
#include "Component.h"

//tempo
#define WORLD_UNIT_TO_PIXEL_UNIT 1.0f
#define PIXEL_UNIT_TO_WORLD_UNIT 1.0f

class SpriteComponent : public Component
{
public:
	SpriteComponent(class GameObject& i_owner);
	void setTexturePath(const std::string& i_path);
	int getZOrder();
	Vector2D getWorldSize();
	size_t getTextureId();
	class Texture* getTexture();
	void setTexture(class Texture* i_texture);
protected:
private:
	class Texture* m_texture = nullptr;
	Vector2D m_world_size;
	int m_local_z_order = 0;
};

