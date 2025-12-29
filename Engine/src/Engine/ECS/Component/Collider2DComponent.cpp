#include "Engine/ECS/Component/Collider2DComponent.h"
#include "Engine/ECS/GameObject.h"

Collider2DComponent::Collider2DComponent(GameObject& i_owner) : Component(i_owner)
{
}

b2Polygon* Collider2DComponent::getCollider()
{
	return &m_collider;
}

b2ShapeDef Collider2DComponent::createShapeDef()
{
    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.enableContactEvents = m_is_collision_event_enable;
    shape_def.enableHitEvents = m_is_hit_event_enable;
    shape_def.density = m_density;
    shape_def.material.friction = m_friction;
    shape_def.material.restitution = m_restitution;
    shape_def.isSensor = !m_is_collision_enable;
    shape_def.enableSensorEvents = m_overlap_event;
    return shape_def;
}

void Collider2DComponent::onContactBeginEvent(Collider2DComponent* i_collider, GameObject* i_game_object)
{
    m_owner.onContactEndEvent(i_collider, i_game_object);
}

void Collider2DComponent::onContactEndEvent(Collider2DComponent* i_collider, GameObject* i_game_object)
{
}

void Collider2DComponent::onOverlapBeginEvent(Collider2DComponent* i_collider, GameObject* i_overlaped_object)
{
    m_owner.onOverlapBeginEvent(i_collider, i_overlaped_object);
}

void Collider2DComponent::onOverlapEndEvent(Collider2DComponent* i_collider, GameObject* i_overlaped_object)
{
    m_owner.onOverlapEndEvent(i_collider, i_overlaped_object);
}

void Collider2DComponent::setShapeId(b2ShapeId i_shape_id)
{
    m_shape_id = i_shape_id;
}

b2ShapeId* Collider2DComponent::getShapeId()
{
    return &m_shape_id;
}

void Collider2DComponent::setBodyId(b2BodyId i_body_id)
{
    m_body_id = i_body_id;
}

b2BodyId* Collider2DComponent::getBodyId()
{
    return &m_body_id;
}
