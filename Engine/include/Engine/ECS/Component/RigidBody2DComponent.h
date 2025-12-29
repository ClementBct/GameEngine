#pragma once
#include "Component.h"

//Tempo ?
#include <box2d/box2d.h>

enum class EBodyType {
	StaticBody,
	DynamicBody,
	Kinematic
};

class RigidBody2DComponent : public Component
{
public:
	RigidBody2DComponent(class GameObject& i_owner, EBodyType i_body_type);
	void onUpdate(double i_dt_s)override;
	EBodyType getBodyType();
	void setBodyId(b2BodyId i_body_id);
	b2BodyId getBodyId();
	void applyForce(const Vector2D& i_force);
	void applyImpulse(const Vector2D& i_impulse);
	void setLinearVelocity(const Vector2D& i_vel);
	void movePosition(const Vector2D& i_position);
	void moveRotation(float i_angle);
	void setGravityScale(float i_gravity_scale);
	float getGravityScale();
	bool m_is_fixed_rotation = false;
	bool m_fixed_x_translation = false;
	bool m_fixed_y_translation = false;
private :
	void setBodyType(EBodyType i_body_type);
	EBodyType m_body_type;
	float m_gravity_scale = 1.0;
	/*Box2D*/
	b2BodyDef m_body_def;
	b2BodyId m_body_id;
};

