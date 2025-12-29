#include "Engine/Core/Camera.h"
#include "Engine/Core/Window.h"
Camera::Camera(class Window& i_window) : m_window(i_window)
{
}

float Camera::getCameraZoom()
{
    return m_camera_zoom;
}

void Camera::setCameraZoom(float i_zoom)
{
    m_camera_zoom = i_zoom;
}

Vector2D Camera::convertWorldPositionToScreenPosition(Vector2D i_world_position)
{
    Vector2D screen_position;
    screen_position.x = (i_world_position.x - m_camera_position.x) * m_camera_zoom + (m_window.getWindowWidth() * 0.5f);
    screen_position.y = (m_window.getWindowHeight() * 0.5f) - (i_world_position.y - m_camera_position.y) * m_camera_zoom;
    return screen_position;
}
