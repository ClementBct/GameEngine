#pragma once

#include "Engine/ECS/GameObject.h"

class CubeSpawner : public GameObject
{
public :
	CubeSpawner(class Scene& i_scene);
	void onKeyPressed(uint32_t i_key) override;
	void onStart();
	void onUpdate(double i_dt_s);
};

