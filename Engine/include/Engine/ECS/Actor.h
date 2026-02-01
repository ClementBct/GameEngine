#pragma once
#include "Engine/ECS/GameObject.h"
#include "Engine/Utils/Math.h"
#include "Engine/ECS/Component/TransformComponent.h"

//Permet de recuperer des inputs à la diff du gameObject

class Actor : public GameObject
{
public:
	Actor(class Scene& i_scene);
	virtual ~Actor();
	virtual void onPossessed();
	virtual void onUnPossessed();
protected:
private:
};