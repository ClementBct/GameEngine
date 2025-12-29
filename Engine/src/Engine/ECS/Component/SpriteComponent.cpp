#include "Engine/ECS/Component/SpriteComponent.h"
#include <SDL3/SDL_render.h>
#include "Engine/ECS/GameObject.h"
#include "Engine/Core/GameManager.h"
#include <print>

SpriteComponent::SpriteComponent(GameObject& i_owner) : Component(i_owner){
}

void SpriteComponent::setTexture(SDL_Texture* i_texture) {
	if (!i_texture) {
		std::println("Texture is not valid");
		return;
	}
	m_texture = i_texture;
	SDL_GetTextureSize(i_texture, &m_texture_w, &m_texture_h);
}

SDL_Texture* SpriteComponent::getTexture() const
{
	return m_texture;
}

int SpriteComponent::getZOrder()
{
	return m_owner.getZOrder() + m_local_z_order;
}

Vector2D SpriteComponent::getWorldSize()
{
	m_world_size.x = m_texture_w * PIXEL_UNIT_TO_WORLD_UNIT * getWorldScale().x;
	m_world_size.y = m_texture_h * PIXEL_UNIT_TO_WORLD_UNIT * getWorldScale().y;
	return m_world_size;
}
