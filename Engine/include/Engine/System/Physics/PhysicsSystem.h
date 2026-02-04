#pragma once

#include "Engine/System/System.h"
#include "Engine/Utils/Math.h"

#include "box2d/box2d.h"
#include <vector>

#define PHYSICS_UNIT_TO_WORLD_UNIT 100.0f
#define WORLD_UNIT_TO_PHYSICS_UNIT 0.01f

Vector2D convertPhysicsPositionToWorldPosition(Vector2D i_physics_position);
Vector2D convertWorldPositionToPhysicsPosition(Vector2D i_world_position);
float convertWorldUnitToPhysicsUnit(float i_world_unit);
float convertPhysicsUnitToWorldUnit(float i_physics_unit);

float convertWorldRotationToPhysicsRotation(float i_deg); 
float convertPhysicsRotationToWorldRotation(float i_rad);

class PhysicsSystem : public System
{
public:
	PhysicsSystem();
	~PhysicsSystem();
	void createPhysicsBody(class GameObject* i_game_object);
	void onFixedUpdate(double i_fixed_dt_s) override;
protected:
private:
	int m_sub_tick_count = 4;
	b2WorldDef m_world_def;
	b2Vec2 m_world_gravity = { 0.0f, -9.89f };
	b2WorldId m_world_id;
};

