#pragma once
#include "Component.h"
#include "box2d/types.h"

class Collider2DComponent : public Component
{
public :
	Collider2DComponent(class GameObject& i_owner);
	b2Polygon* getCollider();
	bool m_is_collision_enable = true;
	bool m_is_collision_event_enable = true;
	bool m_is_hit_event_enable = true;
	bool m_is_collider_visible = false;
	bool m_overlap_event = true;
	float m_friction = 0.5;
	float m_restitution = 0.5;
	float m_density = 0.5;
	b2ShapeDef createShapeDef();
	/**
	 * @brief Callback call when two gameObject touch
	 * @param i_collider the collider that generate the event
	 * @param i_game_object the gameobject that have been touch
	 */
	void onContactBeginEvent(Collider2DComponent* i_collider, GameObject* i_game_object);
	void onContactEndEvent(Collider2DComponent* i_collider, GameObject* i_game_object);
	void onOverlapBeginEvent(Collider2DComponent* i_collider, GameObject* i_overlaped_object);
	void onOverlapEndEvent(Collider2DComponent* i_collider, GameObject* i_overlaped_object);
	void setShapeId(b2ShapeId i_shape_id);
	b2ShapeId* getShapeId();
	void setBodyId(b2BodyId i_body_id);
	b2BodyId* getBodyId();
protected :
	b2Polygon m_collider;
	b2ShapeId m_shape_id;
	b2BodyId m_body_id;
private :
};

