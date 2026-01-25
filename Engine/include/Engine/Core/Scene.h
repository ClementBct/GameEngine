#pragma once
#include <vector>

class Scene
{
public:
	Scene(class GameManager& i_game_mgr);
	~Scene();
	virtual void onLoad();
	void addGameObject(class GameObject* i_game_object);
	void removeGameObject(class GameObject* i_game_object);
	std::vector<class GameObject*>& getGameObjectList();
	const class GameManager& getGameManager()const;
private:
	class GameManager& m_game_mgr;
	std::vector<class GameObject*> m_game_object_list;
};
