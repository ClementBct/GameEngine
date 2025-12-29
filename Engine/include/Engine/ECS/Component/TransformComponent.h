#pragma once
#include "Component.h"
#include "Engine/Utils/Math.h"

class TransformComponent : public Component
{
public :
	TransformComponent(class GameObject& i_owner);
	Vector2D position = { 0.0f,0.0f };
	Vector2D scale = { 1.0f,1.0f };
	float rotation = 0.0f;
};

