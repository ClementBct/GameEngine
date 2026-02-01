#include "Engine/ECS/PlayerController.h"
#include "Engine/ECS/Actor.h"

//System
#include "Engine/System/UI/UISystem.h"
#include "Engine/System/Input/InputSystem.h"

PlayerController::PlayerController(InputSystem& i_input_system, const std::string& i_name) : m_input_system(i_input_system), m_name(i_name){

}

void PlayerController::possess(Actor& i_actor) {
    if (m_actor) {
        m_actor->onUnPossessed();
    }
    m_actor = &i_actor;
    m_actor->onPossessed();
}

void PlayerController::showHUD(UserInterface* i_hud) {
    m_hud = i_hud;
    m_ui_system->setCurrentUserInterface(m_hud);
}