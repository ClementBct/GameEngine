#include "GameObject/Fruit.h"
#include "Engine/ECS/Component/SpriteComponent.h"

#include "Engine/Core/GameManager.h"
#include "Engine/Core/RessourceLoader.h"

Fruit::Fruit(Scene& i_scene) : GameObject(i_scene)
{
	m_main_sprite = new SpriteComponent(*this);
	m_main_sprite->setTexture(getGameMgr()->ressource_loader->loadTexture("Ressources/fruit.png"));
}

void Fruit::onStart() {
	
}

void Fruit::onUpdate(double i_delta_time_s) {
	GameObject::onUpdate(i_delta_time_s);
}
