#pragma once

#include "Engine/ECS/GameObject.h"

class Fruit : public GameObject
{
public:
	Fruit(class Scene& i_scene);
	void onStart() override;
	void onUpdate(double i_delta_time_s) override;
protected:
private:
	class SpriteComponent* m_main_sprite = nullptr;
};

