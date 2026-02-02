#include "GameObject/Fruit.h"
#include "Engine/ECS/Component/SpriteComponent.h"

#include "Engine/Core/GameManager.h"
#include "Engine/Core/RessourceLoader.h"

#include "Engine/Core/Renderer/Texture.h"
#include "Engine/Core/Scene.h"

Fruit::Fruit(Scene& i_scene) : GameObject(i_scene)
{
	m_main_sprite = new SpriteComponent(*this);
	Texture* texture = getScene().getGameManager().getRessourceLoader().createTexture("fruit.png");
	m_main_sprite->setTexture(texture);
}

void Fruit::onStart() {
	
}

void Fruit::onUpdate(double i_dt_s) {
	GameObject::onUpdate(i_dt_s);
}
void Fruit::onFixedUpdate(double i_fixed_dt_s) {
	GameObject::onUpdate(i_fixed_dt_s);
}
