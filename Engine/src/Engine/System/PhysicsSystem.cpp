#include "Engine/System/PhysicsSystem.h"
#include "Engine/ECS/GameObject.h"
#include "Engine/ECS/Component/BoxCollider2DComponent.h"
#include "Engine/ECS/Component/RigidBody2DComponent.h"

#include <print>

#include <box2d/box2d.h>


Vector2D convertPhysicsPositionToWorldPosition(Vector2D i_physics_position)
{
	Vector2D world_position;
	world_position.x = i_physics_position.x * PHYSICS_UNIT_TO_WORLD_UNIT;
	world_position.y = i_physics_position.y * PHYSICS_UNIT_TO_WORLD_UNIT;
	return world_position;
}

Vector2D convertWorldPositionToPhysicsPosition(Vector2D i_world_position)
{
	Vector2D physics_position;
	physics_position.x = i_world_position.x * WORLD_UNIT_TO_PHYSICS_UNIT;
	physics_position.y = i_world_position.y * WORLD_UNIT_TO_PHYSICS_UNIT;
	return physics_position;
}

float convertWorldRotationToPhysicsRotation(float i_deg) { 
	return -degToRad(i_deg); 
}
float convertPhysicsRotationToWorldRotation(float i_rad) { 
	return -radToDeg(i_rad); 
}

float convertWorldUnitToPhysicsUnit(float i_world_unit)
{
	return i_world_unit*WORLD_UNIT_TO_PHYSICS_UNIT;
}

float convertPhysicsUnitToWorldUnit(float i_physics_unit)
{
	return i_physics_unit*PHYSICS_UNIT_TO_WORLD_UNIT;
}

PhysicsSystem::PhysicsSystem()
{
	m_world_def = b2DefaultWorldDef();
	m_world_def.gravity = m_world_gravity;
	m_world_id = b2CreateWorld(&m_world_def);
}

PhysicsSystem::~PhysicsSystem()
{
	b2DestroyWorld(m_world_id);
}

void PhysicsSystem::updatePhysicsSystem(double i_dt_s)
{
	b2World_Step(
		m_world_id,
		i_dt_s,
		m_sub_tick_count
	);
	b2ContactEvents contact_events = b2World_GetContactEvents(m_world_id);
	b2SensorEvents sensor_events = b2World_GetSensorEvents(m_world_id);
	//Begin contact
	for (int i = 0; i < contact_events.beginCount; ++i)
	{
		b2ContactBeginTouchEvent* begin_event = contact_events.beginEvents + i;

		void* user_data_a = b2Shape_GetUserData(begin_event->shapeIdA);
		void* user_data_b = b2Shape_GetUserData(begin_event->shapeIdB);

		Collider2DComponent* collider_a = static_cast<Collider2DComponent*>(user_data_a);
		Collider2DComponent* collider_b = static_cast<Collider2DComponent*>(user_data_b);

		collider_a->onContactBeginEvent(collider_a, collider_b->getOwner());
		collider_b->onContactBeginEvent(collider_b, collider_a->getOwner());
	}
	//End contact
	for (int i = 0; i < contact_events.endCount; ++i)
	{
		b2ContactEndTouchEvent* end_event = contact_events.endEvents + i;

		void* user_data_a = b2Shape_GetUserData(end_event->shapeIdA);
		void* user_data_b = b2Shape_GetUserData(end_event->shapeIdB);

		Collider2DComponent* collider_a = static_cast<Collider2DComponent*>(user_data_a);
		Collider2DComponent* collider_b = static_cast<Collider2DComponent*>(user_data_b);

		collider_a->onContactEndEvent(collider_a, collider_b->getOwner());
		collider_b->onContactEndEvent(collider_b, collider_a->getOwner());
	}
	//Begin overlap
	for (int i = 0; i < sensor_events.beginCount;i++) {
		b2SensorBeginTouchEvent* begin_event = sensor_events.beginEvents + i;

		void* overlaped_collider_data = b2Shape_GetUserData(begin_event->sensorShapeId);
		void* visitor_collider_data = b2Shape_GetUserData(begin_event->visitorShapeId);

		Collider2DComponent* overlaped_collider = static_cast<Collider2DComponent*>(overlaped_collider_data);
		Collider2DComponent* visitor_collider = static_cast<Collider2DComponent*>(visitor_collider_data);

		overlaped_collider->onOverlapBeginEvent(overlaped_collider, visitor_collider->getOwner());
	}
	//End overlap
	for (int i = 0; i < sensor_events.endCount;i++) {
		b2SensorEndTouchEvent* end_event = sensor_events.endEvents + i;

		void* overlaped_collider_data = b2Shape_GetUserData(end_event->sensorShapeId);
		void* visitor_collider_data = b2Shape_GetUserData(end_event->visitorShapeId);

		Collider2DComponent* overlaped_collider = static_cast<Collider2DComponent*>(overlaped_collider_data);
		Collider2DComponent* visitor_collider = static_cast<Collider2DComponent*>(visitor_collider_data);

		overlaped_collider->onOverlapEndEvent(overlaped_collider, visitor_collider->getOwner());
	}
}

void PhysicsSystem::createPhysicsBody(GameObject* i_game_object)
{
	auto rigid_body = i_game_object->getComponent<RigidBody2DComponent>();
	auto colliders_list = i_game_object->getComponents<Collider2DComponent>();

	if (!rigid_body) {
		std::println("gameObject has no rigid body component");
		return;
	}
	if (colliders_list.empty()) {
		std::println("gameObject has no collider");
		return;
	}
	b2BodyDef body_def = b2DefaultBodyDef();

	switch (rigid_body->getBodyType()) {
	case EBodyType::StaticBody :
		body_def.type = b2_staticBody; break;
	case EBodyType::DynamicBody:
		body_def.type = b2_dynamicBody; break;
	case EBodyType::Kinematic:
		body_def.type = b2_kinematicBody; break;
	default :
		std::println("Unknown body type");
	}
	body_def.motionLocks.angularZ = rigid_body->m_is_fixed_rotation;
	body_def.motionLocks.linearX = rigid_body->m_fixed_x_translation;
	body_def.motionLocks.linearY = rigid_body->m_fixed_y_translation;
	Vector2D physics_position = convertWorldPositionToPhysicsPosition(rigid_body->getWorldPosition());
	body_def.gravityScale = rigid_body->getGravityScale();
	body_def.position = { physics_position.x , physics_position.y };
	body_def.rotation = b2MakeRot(convertWorldRotationToPhysicsRotation(rigid_body->getWorldRotation()));
	b2BodyId body_id = b2CreateBody(m_world_id, &body_def);
	// Ajouter les colliders (si présents)
	for (auto collider : colliders_list) {
		b2ShapeDef shape_def = collider->createShapeDef();
		b2ShapeId shape_id = b2CreatePolygonShape(body_id, &shape_def, collider->getCollider());
		collider->setShapeId(shape_id);
		collider->setBodyId(body_id);
		b2Shape_SetUserData(shape_id, collider);
	}
	rigid_body->setBodyId(body_id);
}
