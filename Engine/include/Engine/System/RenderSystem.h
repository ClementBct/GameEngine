#pragma once
#include <vector>

class RenderSystem
{
public:
	RenderSystem(class Renderer& i_renderer, class Camera& i_camera);
	~RenderSystem();
	void loadTexture(class GameObject* i_game_object);
	void renderScene(class Scene* i_scene);
private :

	class Renderer& m_renderer;
	class Camera& m_camera;
	void drawSprite(class SpriteComponent* i_sprite, float i_camera_zoom);
	void drawCollider(class Collider2DComponent* i_collider);
};

