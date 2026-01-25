#include "Engine/ECS/Component/SpriteComponent.h"
#include <SDL3/SDL_render.h>
#include "Engine/ECS/GameObject.h"
#include "Engine/Core/GameManager.h"
#include "Engine/Core/Renderer/Texture.h"
#include <print>
#include <iostream>

SpriteComponent::SpriteComponent(GameObject& i_owner) : Component(i_owner){
}

int SpriteComponent::getZOrder()
{
	return m_owner.getZOrder() + m_local_z_order;
}

Vector2D SpriteComponent::getWorldSize()
{
	if(m_texture){
		m_world_size.x = m_texture->width * PIXEL_UNIT_TO_WORLD_UNIT * getWorldScale().x;
		m_world_size.y = m_texture->height * PIXEL_UNIT_TO_WORLD_UNIT * getWorldScale().y;
	}
	return m_world_size;
}
size_t SpriteComponent::getTextureId() {
	if (m_texture) {
		return m_texture->id;
	}
	return -1;
}

Texture* SpriteComponent::getTexture() {
	return m_texture;
}
void SpriteComponent::setTexture(Texture* i_texture) {
	if (!i_texture) {
		std::cout << "Texture is not valid\n";
		return;
	}
	m_texture = i_texture;
}
