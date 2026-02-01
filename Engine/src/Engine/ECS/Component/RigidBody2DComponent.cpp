#include "Engine/ECS/Component/RigidBody2DComponent.h"
#include "Engine/ECS/GameObject.h"
#include "Engine/System/Physics/PhysicsSystem.h"

RigidBody2DComponent::RigidBody2DComponent(GameObject& i_owner, EBodyType i_body_type) : Component(i_owner), m_body_type(i_body_type)
{
}

void RigidBody2DComponent::onUpdate(double i_dt_s)
{
	b2Vec2 physics_position = b2Body_GetPosition(m_body_id);
	b2Rot rotation = b2Body_GetRotation(m_body_id);
	float rad_angle = b2Rot_GetAngle(rotation);
	Vector2D world_position = convertPhysicsPositionToWorldPosition({ physics_position.x, physics_position.y });
	m_owner.transform->position = world_position;
	m_owner.transform->rotation = convertPhysicsRotationToWorldRotation(rad_angle);;
}

EBodyType RigidBody2DComponent::getBodyType()
{
	return m_body_type;
}

void RigidBody2DComponent::setBodyId(b2BodyId i_body_id)
{
	m_body_id = i_body_id;
}

b2BodyId RigidBody2DComponent::getBodyId()
{
	return m_body_id;
}

void RigidBody2DComponent::applyForce(const Vector2D& force)
{
    if (m_body_type != EBodyType::DynamicBody)
    {
        // Static/Kinematic ne réagissent pas aux forces
        return;
    }

    //b2Body_ApplyForce(m_body_id, convertToB2Vec2(force), b2Body_GetPosition(m_body_id));
}

void RigidBody2DComponent::applyImpulse(const Vector2D& i_impulse)
{
    if (m_body_type != EBodyType::DynamicBody) {
        return;
    }
    b2Vec2 impulse;
    impulse.x = i_impulse.x;
    impulse.y = i_impulse.y;
    b2Body_ApplyLinearImpulse(m_body_id, impulse, b2Body_GetPosition(m_body_id), true);
}

void RigidBody2DComponent::setLinearVelocity(const Vector2D& i_velolicty)
{
    if (m_body_type == EBodyType::DynamicBody || m_body_type == EBodyType::Kinematic) {
        b2Vec2 velocity;
        velocity.x = i_velolicty.x;
        velocity.y = i_velolicty.y;
        b2Body_SetLinearVelocity(m_body_id, velocity);
    }

}

void RigidBody2DComponent::movePosition(const Vector2D& pos)
{
    if (m_body_type == EBodyType::Kinematic || m_body_type == EBodyType::DynamicBody)
    {
        //b2Body_SetTransform(m_body_id, convertToB2Vec2(pos), b2Body_GetRotation(m_body_id));
    }
}

void RigidBody2DComponent::moveRotation(float angle)
{
    if (m_body_type != EBodyType::StaticBody)
    {
        //b2Body_SetTransform(m_body_id, b2Body_GetPosition(m_body_id), degToRad(angle));
    }
}

void RigidBody2DComponent::setGravityScale(float i_gravity_scale)
{
    m_gravity_scale = i_gravity_scale;
}

float RigidBody2DComponent::getGravityScale()
{
    return m_gravity_scale;
}

void RigidBody2DComponent::setBodyType(EBodyType i_body_type)
{
    m_body_type = i_body_type;
}
