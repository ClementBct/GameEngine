#include "Engine/ECS/GameObject.h"
#include "Engine/Core/Scene.h"
#include <print>

GameObject::GameObject(Scene& i_scene) : Entity() , m_scene(i_scene){
	transform = new TransformComponent(*this);
}
GameObject::~GameObject() {
}

int GameObject::getZOrder()
{
	return m_z_order;
}
const Scene& GameObject::getScene() const{
	return m_scene;
}

void GameObject::setTag(const std::string& i_tag) {
	m_tag = i_tag;
}
std::string GameObject::getTag() {
	return m_tag;
}

void GameObject::onContactBeginEvent(Collider2DComponent* i_collider, GameObject* i_game_object)
{
}

void GameObject::onContactEndEvent(Collider2DComponent* i_collider, GameObject* i_game_object)
{
}

void GameObject::onOverlapBeginEvent(Collider2DComponent* i_collider, GameObject* i_overlaped_object)
{
}

void GameObject::onOverlapEndEvent(Collider2DComponent* i_collider, GameObject* i_overlaped_object)
{
}
