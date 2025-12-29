#pragma once

#include "Engine/Utils/Math.h"

class Camera
{
public :
	Camera(class Window& i_window);
	float getCameraZoom();
	void setCameraZoom(float i_zoom);
	Vector2D convertWorldPositionToScreenPosition(Vector2D i_world_position);
private:
	class Window& m_window;
	float m_camera_zoom = 1.0f;
	Vector2D m_camera_position = { 0.0f,0.0f };
};

