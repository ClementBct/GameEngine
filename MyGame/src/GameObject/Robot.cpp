#include "GameObject/Robot.h"

//Component
#include "Engine/ECS/Component/SpriteComponent.h"
#include "Engine/ECS/Component/RigidBody2DComponent.h"
#include "Engine/ECS/Component/BoxCollider2DComponent.h"
#include "Engine/ECS/Component/Sound2DComponent.h"


#include "Engine/Core/PlayerController.h"
#include "Engine/Core/GameManager.h"
#include "Engine/Core/RessourceLoader.h"
#include "Engine/Core/Renderer/Texture.h"
#include "Engine/Core/Scene.h"
//System
#include "Engine/System/Physics/PhysicsSystem.h"
#include "Engine/System/Input/InputSystem.h"
#include "Engine/System/UI/UISystem.h"

#include <print>
#include "GameObject/Cube.h"
#include "Engine/Core/Camera.h"

//ui
#include "UserInterface/mainUserInterface.h"

Robot::Robot(Scene& i_scene) : GameObject(i_scene)
{
    setTag("Robot");
	m_robot_sprite = createComponent<SpriteComponent>(*this);
    Texture* main_texture = getScene().getGameManager().getRessourceLoader().createTexture("robot.png");
    m_robot_sprite->setTexture(main_texture);
	transform->scale = { 0.2f,0.2f };
	m_rb = createComponent<RigidBody2DComponent>(*this, EBodyType::DynamicBody);
    m_rb->setGravityScale(0.0f);
    m_rb->m_is_fixed_rotation = true;
	m_box_collider = createComponent<BoxCollider2DComponent>(*this);
	m_box_collider->setBoxColliderSize(50.0f, 100.0f);
    m_box_collider->m_is_collision_enable = true;
    m_box_collider->m_is_collision_event_enable = true;
    m_box_collider->m_is_collider_visible = true;
    m_box_collider->m_friction = 0.0f;
    m_box_collider->m_restitution = 0.0f;


    m_attraction_box = createComponent<BoxCollider2DComponent>(*this);
    m_attraction_box->setBoxColliderSize(200.0f, 200.0f);
    m_attraction_box->setLocalPosition({ 100.0f,100.0f });
    m_attraction_box->m_is_collision_enable = false;
    m_attraction_box->m_is_collider_visible = true;
    m_attraction_box->m_overlap_event = true;

    //fonction de création de composant interdiction de crée un new
    m_audio = createComponent<Sound2DComponent>(*this, "Ressources/pop.wav");

}

void Robot::onStart() {
    MainUserInterface& ui = getScene().getGameManager().getUISystem().createUserInterface<MainUserInterface>(getScene().getGameManager().getPlayerController(), getScene().getGameManager().getRessourceLoader());
    getScene().getGameManager().getPlayerController().showUI(ui);
}
void Robot::onUpdate(double i_dt_s) {
	//Must call parent onUpdate
	GameObject::onUpdate(i_dt_s);
	updateMovement(i_dt_s);
    //Vector2D mouse_world_pos = getScene().getGameManager().m_camera->convertScreenPositionToWorldPosition(getScene().getGameManager().m_input_system->getMouseScreenPosition());
    //std::println("{} : {}", mouse_world_pos.x, mouse_world_pos.y);
}

void Robot::onFixedUpdate(double i_fixed_dt_s) {
    GameObject::onFixedUpdate(i_fixed_dt_s);
}

void Robot::setRobotSpeed(float i_speed) {
	m_robot_speed = i_speed;
}

void Robot::updateMovement(double i_dt_s)
{
    m_move_direction_x = 0.f;
    m_move_direction_y = 0.f;
    /*
    // Lecture des touches
    if (getGameMgr()->m_input_system->isKeyPressed(SDLK_D)) m_move_direction_x += 1.f;
    if (getGameMgr()->m_input_system->isKeyPressed(SDLK_Q)) m_move_direction_x -= 1.f;
    if (getGameMgr()->m_input_system->isKeyPressed(SDLK_Z)) m_move_direction_y += 1.f;
    if (getGameMgr()->m_input_system->isKeyPressed(SDLK_S)) m_move_direction_y -= 1.f;
    */
    // 2️ Normalisation diagonale
    float length = std::sqrt(m_move_direction_x * m_move_direction_x + m_move_direction_y * m_move_direction_y);
    if (length > 1.f) {
        m_move_direction_x /= length;
        m_move_direction_y /= length;
    }
    Vector2D velocity;
    velocity.x = m_move_direction_x * m_robot_speed;
    velocity.y = m_move_direction_y * m_robot_speed;

    // On demande au corps cinématique de se déplacer
    m_rb->setLinearVelocity(velocity);
}

float Robot::getRobotSpeed() {
	return m_robot_speed;
}

void Robot::onContactBeginEvent(Collider2DComponent* i_collider, GameObject* i_game_object)
{
    if (i_game_object->getTag() == "Ground") {
        std::println("Touch !");
    }
}

void Robot::onContactEndEvent(class Collider2DComponent* i_collider, GameObject* i_game_object) {
    if (i_game_object->getTag() == "Ground") {
        std::println("No Touch !");
    }
}
void Robot::onOverlapBeginEvent(class Collider2DComponent* i_collider, GameObject* i_overlaped_object) {
    if (i_overlaped_object->getTag() == "Ground") {
        std::println("C'est le sol!!!");
        //getGameMgr()->spawnGameObject<Cube>({200.0,100.0});
    }
}