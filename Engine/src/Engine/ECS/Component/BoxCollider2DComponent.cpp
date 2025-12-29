#include "Engine/ECS/Component/BoxCollider2DComponent.h"
#include "Engine/System/PhysicsSystem.h"

BoxCollider2DComponent::BoxCollider2DComponent(GameObject& i_owner) : Collider2DComponent(i_owner)
{
	m_collider = b2MakeBox((convertWorldUnitToPhysicsUnit(m_box_width) / 2.0f), (convertWorldUnitToPhysicsUnit(m_box_height) / 2.0f));
}


void BoxCollider2DComponent::setBoxColliderSize(float i_width, float i_height)
{
	m_box_width = i_width;
	m_box_height = i_height;
	m_collider = b2MakeBox((convertWorldUnitToPhysicsUnit(m_box_width) / 2.0f), (convertWorldUnitToPhysicsUnit(m_box_height) / 2.0f));
}
