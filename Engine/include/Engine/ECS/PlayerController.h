#pragma once

#include <string>

class PlayerController {
public:
    PlayerController(class InputSystem& i_input_system, const std::string& i_name);
    //void handleInput(const InputEvent& event);
    void possess(class Actor& i_game_object);
    void showHUD(class UserInterface* hud);
    //Ici qu'on fait l'interface entre input et action (bind jump to spacebar)
protected:

private:
    std::string m_name = "";
    class Actor* m_actor = nullptr;
    class UserInterface* m_hud = nullptr;
    class UISystem* m_ui_system = nullptr;
    class InputSystem& m_input_system;
};