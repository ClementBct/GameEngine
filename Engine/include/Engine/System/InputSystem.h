#pragma once
#include "Engine/System/System.h"
#include <vector>
#include <functional>
#include "SDL3/SDL_keycode.h"

class InputSystem : public System
{
public :
	InputSystem();
	~InputSystem();
	void processInput(class Scene* i_scene);
	void registerQuitCallback(std::function<void()> i_callback);
	bool isKeyPressed(SDL_Keycode i_key)const;
private :
	std::function<void()> m_quit_callback = nullptr;
	std::unordered_map<SDL_Keycode, bool> m_key_states; // état actuel des touches
};

