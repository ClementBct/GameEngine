#pragma once

#include <string>

#define DEFAULT_UPDATE_ORDER 100

#include "Engine/Utils/Math.h"

class Component
{
public :
	Component(class GameObject& owner);
	virtual ~Component();
	class GameObject* getOwner(void);
	virtual void onUpdate(double i_dt_s);
	virtual void onFixedUpdate(double i_fixed_dt_s);
	/*Component ID*/
	void setId(const size_t i_id);
	const size_t getComponentId();
	/*Transform*/
	Vector2D getLocalPosition();
	Vector2D getLocalScale();
	float getLocalRotation();
	void setLocalPosition(Vector2D i_local_position);
	void setLocalScale(Vector2D i_local_scale);
	void setLocalRotation(float i_local_rotation);
	Vector2D getWorldPosition();
	Vector2D getWorldScale();
	float getWorldRotation();
protected :
	class GameObject& m_owner;
private :
	Vector2D m_local_position = { 0.0f,0.0f };
	float m_local_rotation = 0.0f;
	Vector2D m_local_scale = { 1.0f,1.0f };
	size_t m_id;
};

