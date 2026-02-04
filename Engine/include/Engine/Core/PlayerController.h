#pragma once

#include "Engine/System/Input/Input.h"

#include <string>

class InputSystem;
class UISystem;
class UserInterface;
class Actor;

class PlayerController {
public:
    PlayerController(InputSystem& i_input_system,UISystem& i_ui_system);
    virtual ~PlayerController();
    //void handleInput(const InputEvent& event);
    void possess(Actor& i_game_object);
    void showUI(UserInterface& i_ui);
    //Ici qu'on fait l'interface entre input et action (bind jump to spacebar)
    UserInterface* getHUD();
    virtual void onKeyPressed(const EKeyboardKey i_key); //callback
    virtual void onKeyReleased(const EKeyboardKey i_key); //callback
protected:

private:
    Actor* m_actor = nullptr;
    UserInterface* m_hud = nullptr;
    UISystem& m_ui_system;
    InputSystem& m_input_system;
};