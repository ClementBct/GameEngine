#include "GameObject/CubeSpawner.h"
#include "GameObject/Cube.h"
#include <print>

CubeSpawner::CubeSpawner(Scene& i_scene) : GameObject(i_scene)
{
}

void CubeSpawner::onKeyPressed(uint32_t i_key)
{
}


void CubeSpawner::onStart() {
	std::print("Hello");
}

void CubeSpawner::onUpdate(double i_dt_s) {
	GameObject::onUpdate(i_dt_s);
}