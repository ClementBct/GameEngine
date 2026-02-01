#pragma once
#include "Entity.h"
#include "Engine/Utils/Math.h"
#include "Engine/ECS/Component/TransformComponent.h"

class GameObject : public Entity
{
public :
	GameObject(class Scene& i_scene);
	virtual ~GameObject();
	TransformComponent* transform;
	const class Scene& getScene()const;
	int getZOrder();
	/*KeyBoard Event*/
	bool m_is_keyboardEventEnable = true;
	virtual void onKeyPressed(uint32_t i_key);
	virtual	void onKeyReleased(uint32_t i_key);
	void setTag(const std::string& i_tag);
	std::string getTag();
	virtual void onContactBeginEvent(class Collider2DComponent* i_collider, GameObject* i_game_object);
	virtual void onContactEndEvent(class Collider2DComponent* i_collider, GameObject* i_game_object);
	virtual void onOverlapBeginEvent(class Collider2DComponent* i_collider, GameObject* i_overlaped_object);
	virtual void onOverlapEndEvent(class Collider2DComponent* i_collider, GameObject* i_overlaped_object);
protected :
private :
	std::string m_tag;
	int m_z_order = 0;
	class Scene& m_scene;
};
