#pragma once

#include "Engine/ECS/GameObject.h"

#define DEFAULT_ROBOT_SPEED 5.0f
#define TIME_BETWEEN_SPEED_UPGRADE_S 1.0f

class Robot : public GameObject
{
public:
	Robot(class Scene& i_scene);
	void onStart() override;
	void onUpdate(double i_dt_s) override;
	void onFixedUpdate(double i_fixed_dt_s)override;
	float getRobotSpeed();
	void setRobotSpeed(float i_speed);
	void onKeyPressed(uint32_t i_key) override;
	void onKeyReleased(uint32_t i_key) override;

	void onContactBeginEvent(class Collider2DComponent* i_collider, GameObject* i_game_object)override;
	void onContactEndEvent(class Collider2DComponent* i_collider, GameObject* i_game_object)override;
	void onOverlapBeginEvent(class Collider2DComponent* i_collider, GameObject* i_overlaped_object)override;

protected :
	float m_robot_speed = DEFAULT_ROBOT_SPEED;
private :
	void updateMovement(double i_dt_s);
	float m_move_direction_x = 0.0f;
	float m_move_direction_y = 0.0f;

	double m_time_since_last_speed_upgrade_s = 0;
	class SpriteComponent* m_robot_sprite = nullptr;
	class RigidBody2DComponent* m_rb = nullptr;
	class BoxCollider2DComponent* m_box_collider = nullptr;
	class BoxCollider2DComponent* m_attraction_box = nullptr;
	class Sound2DComponent* m_audio = nullptr;
	class MainUserInterface* m_hud = nullptr;
};

