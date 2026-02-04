#pragma once

#include "Engine/ECS/GameObject.h"

class CubeSpawner : public GameObject
{
public :
	CubeSpawner(class Scene& i_scene);
	void onStart();
	void onUpdate(double i_dt_s);
};

