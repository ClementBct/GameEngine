#pragma once
#include "Engine/System/System.h"
#include <vector>

class RenderSystem : public System
{
public:
	RenderSystem(class Renderer& i_renderer, class Camera& i_camera);
	~RenderSystem();
	void renderScene(class Scene* i_scene);
private :

	class Renderer& m_renderer;
	class Camera& m_camera;
	void drawSprite(class SpriteComponent* i_sprite, float i_camera_zoom);
	void drawCollider(class Collider2DComponent* i_collider);
};

