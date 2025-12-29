#pragma once
#include "Collider2DComponent.h"

//tempo ?
#include <box2d/box2d.h>

class BoxCollider2DComponent : public Collider2DComponent
{
public :
	BoxCollider2DComponent(class GameObject& i_owner);
	/**
	 * @brief Define the size of the collider box, in world unit
	 * @param i_width the width of the box in world unit
	 * @param i_height the height of the box in world unit
	 */
	void setBoxColliderSize(float i_width, float i_height);
private :
	const float DEFAULT_BOX_WIDTH = 10.0f;
	const float DEFAULT_BOX_HEIGHT = 10.0f;
	float m_box_width = DEFAULT_BOX_WIDTH;
	float m_box_height = DEFAULT_BOX_HEIGHT;
};

