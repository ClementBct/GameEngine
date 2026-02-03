#pragma once

#include <string>

class InputSystem;
class UISystem;
class UserInterface;
class Actor;

class PlayerController {
public:
    PlayerController(InputSystem& i_input_system,UISystem& i_ui_system);
    //void handleInput(const InputEvent& event);
    void possess(Actor& i_game_object);
    void showUI(UserInterface& i_ui);
    //Ici qu'on fait l'interface entre input et action (bind jump to spacebar)
    UserInterface* getHUD();
protected:

private:
    class Actor* m_actor = nullptr;
    class UserInterface* m_hud = nullptr;
    class UISystem& m_ui_system;
    class InputSystem& m_input_system;
};