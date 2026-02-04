#include "Engine/ECS/Component/Component.h"
#include "Engine/ECS/GameObject.h"

Component::Component(GameObject& i_owner) : m_owner(i_owner){
}

Component::~Component() {
}

GameObject* Component::getOwner() {
	return &m_owner;
}

void Component::onUpdate(double i_dt_s)
{
	(void)i_dt_s;
}
void Component::onFixedUpdate(double i_fixed_dt_s) {
	(void)i_fixed_dt_s;
}
Vector2D Component::getLocalPosition()
{
	return m_local_position;
}

Vector2D Component::getLocalScale()
{
	return m_local_scale;
}

float Component::getLocalRotation()
{
	return m_local_rotation;
}

void Component::setLocalPosition(Vector2D i_local_position)
{
	m_local_position = i_local_position;
}

void Component::setLocalScale(Vector2D i_local_scale)
{
	m_local_scale = i_local_scale;
}

void Component::setLocalRotation(float i_local_rotation)
{
	m_local_rotation = i_local_rotation;
}

Vector2D Component::getWorldPosition()
{
	return m_owner.transform->position + m_local_position;
}

Vector2D Component::getWorldScale()
{
	return m_owner.transform->scale * m_local_scale;
}

float Component::getWorldRotation()
{
	return m_owner.transform->rotation + m_local_rotation;
}

void Component::setId(const size_t i_id)
{
	m_id = i_id;
}

const size_t Component::getComponentId()
{
	return m_id;
}
