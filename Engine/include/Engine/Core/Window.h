#pragma once

#include <string>

struct SDL_Window;

class Window
{
public :
	Window(const std::string& i_window_name);
	~Window();
	SDL_Window* getWindow();
	int getWindowHeight();
	int getWindowWidth();
private :
	SDL_Window* m_window = nullptr;
	int m_screen_width = 1280;
	int m_screen_height = 720;
	const std::string m_window_name = "Default window name";
};

