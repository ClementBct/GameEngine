#pragma once

#include <vector>
#include <string>

class GameManager;
class PlayerController;
class GameObject;

class Scene
{
public:
	Scene(GameManager& i_game_mgr);
	virtual ~Scene();
	virtual void onLoad();
	virtual void onUnLoad();
	virtual void onUpdate(double i_dt_s);
	virtual void onFixedUpdate(double i_fixed_dt_s);
	bool destroyGameObject(GameObject* i_game_object);

	const std::vector<GameObject*>& getGameObjectList()const;
	
	const GameManager& getGameManager()const;
	void setPlayerController(PlayerController* i_pc);

	template<typename T, typename... Args>
	T* spawnGameObject(Args&&... i_args) {
		static_assert(std::is_base_of_v<GameObject, T>,
			"T must derive from GameObject");
		auto gameObject = new T(std::forward<Args>(i_args)...);
		m_gameObjectList.push_back(gameObject);
		return gameObject;
	}
private:
	GameManager& m_game_mgr;
	std::vector<GameObject*> m_gameObjectList;
	PlayerController* m_playerController = nullptr;
};
