#include "Engine/ECS/Component/CircleCollider2DComponent.h"

CircleCollider2DComponent::CircleCollider2DComponent(GameObject& i_owner) : Collider2DComponent(i_owner)
{
	//m_collider = b2MakeBox((convertWorldUnitToPhysicsUnit(m_box_width) / 2.0f), (convertWorldUnitToPhysicsUnit(m_box_height) / 2.0f));
	//m_collider = b2MakeC
}

void CircleCollider2DComponent::setCircleRadius(float i_radius)
{
	m_circle_radius = i_radius;
}
