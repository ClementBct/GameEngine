#pragma once
#include "Collider2DComponent.h"
class CircleCollider2DComponent : public Collider2DComponent
{
public :
	CircleCollider2DComponent(class GameObject& i_owner);
	void setCircleRadius(float i_radius);
private :
	const float DEFAULT_CIRCLE_RADIUS = 10.0f;
	float m_circle_radius = DEFAULT_CIRCLE_RADIUS;
};

