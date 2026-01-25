#include "GameObject/Ground.h"
#include "Engine/Core/GameManager.h"
#include "Engine/Core/RessourceLoader.h"
#include "Engine/Core/Renderer/Texture.h"
#include "Engine/Core/Scene.h"
//Component include
#include "Engine/ECS/Component/SpriteComponent.h"
#include "Engine/ECS/Component/RigidBody2DComponent.h"
#include "Engine/ECS/Component/BoxCollider2DComponent.h"

Ground::Ground(class Scene& i_scene) : GameObject(i_scene)
{
	setTag("Ground");
	m_main_sprite = new SpriteComponent(*this);
	m_main_sprite->setTexture(getScene().getGameManager().m_ressource_loader->loadTexture("ground.png"));
	m_rb = new RigidBody2DComponent(*this, EBodyType::StaticBody);
	m_box_collider = new BoxCollider2DComponent(*this);
	m_box_collider->setBoxColliderSize(500.0f, 20.0f);
	m_box_collider->m_is_collider_visible = true;
}

void Ground::onStart()
{
}

void Ground::onUpdate(double i_dt_s)
{
	GameObject::onUpdate(i_dt_s);
}
