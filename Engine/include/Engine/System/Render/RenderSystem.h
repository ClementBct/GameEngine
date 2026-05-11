#pragma once
#include "Engine/System/System.h"
#include <vector>

class UserInterface;
class Scene;

class RenderSystem : public System
{
public:
	RenderSystem(class Renderer& i_renderer, class Camera& i_camera);
	virtual ~RenderSystem();
	void renderFrame(Scene* scene,std::vector<UserInterface*>& i_ui_list);
private :
	void renderUserInterface(UserInterface* i_ui);
	void renderScene(Scene* i_scene);
	class Renderer& m_renderer;
	class Camera& m_camera;
	void drawSprite(class SpriteComponent* i_sprite, float i_camera_zoom);
	void drawCollider(class Collider2DComponent* i_collider);
};

