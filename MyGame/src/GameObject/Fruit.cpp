#include "GameObject/Fruit.h"
#include "Engine/ECS/Component/SpriteComponent.h"

#include "Engine/Core/GameManager.h"
#include "Engine/Core/RessourceLoader.h"

#include "Engine/Core/Renderer/Texture.h"
#include "Engine/Core/Scene.h"

Fruit::Fruit(Scene& i_scene) : GameObject(i_scene)
{
	m_main_sprite = new SpriteComponent(*this);
	m_main_sprite->setTexture(getScene().getGameManager().m_ressource_loader->loadTexture("fruit.png"));
}

void Fruit::onStart() {
	
}

void Fruit::onUpdate(double i_delta_time_s) {
	GameObject::onUpdate(i_delta_time_s);
}
