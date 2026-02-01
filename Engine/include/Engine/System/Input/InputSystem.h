#pragma once
#include "Engine/System/System.h"
#include <vector>
#include <functional>
#include "SDL3/SDL_keycode.h"

#include "Engine/Utils/Math.h"
#include "Engine/System/Input/Input.h"

class InputSystem : public System
{
public :
	InputSystem();
	~InputSystem();
	void onUpdate(double i_dt_s) override;
	void registerQuitCallback(std::function<void()> i_callback);
	bool isKeyPressed(const SDL_Keycode i_key)const;
	Vector2D getMouseScreenPosition();
private :
	std::function<void()> m_quit_callback = nullptr;
	std::unordered_map<SDL_Keycode, bool> m_key_states; // état actuel des touches
	Vector2D m_mouse_screen_position;
	EKeyboardKey sdlKeyToKeyBoardKey(const SDL_Keycode i_key);
};

