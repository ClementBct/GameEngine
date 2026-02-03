#include "Engine/ECS/PlayerController.h"
#include "Engine/ECS/Actor.h"

//System
#include "Engine/System/UI/UISystem.h"
#include "Engine/System/Input/InputSystem.h"

PlayerController::PlayerController(InputSystem& i_input_system,UISystem& i_ui_system) : m_input_system(i_input_system), m_ui_system(i_ui_system){

}

void PlayerController::possess(Actor& i_actor) {
    if (m_actor) {
        m_actor->onUnPossessed();
    }
    m_actor = &i_actor;
    m_actor->onPossessed();
}

void PlayerController::showUI(UserInterface& i_ui) {
    m_hud = &i_ui;
    m_ui_system.addActiveUserInterface(&i_ui);
}

UserInterface* PlayerController::getHUD() {
    return m_hud;
}