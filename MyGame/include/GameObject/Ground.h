#pragma once
#include "Engine/ECS/GameObject.h"

class Ground :public GameObject
{
public:
	Ground(class Scene& i_scene);
	void onStart() override;
	void onUpdate(double i_dt_s) override;
protected:
private:
	class SpriteComponent* m_main_sprite = nullptr;
	class RigidBody2DComponent* m_rb = nullptr;
	class BoxCollider2DComponent* m_box_collider = nullptr;
};

