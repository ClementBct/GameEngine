#pragma once

#include <vector>
#include <string>

class GameManager;
class PlayerController;

class Scene
{
public:
	Scene(GameManager& i_game_mgr);
	virtual ~Scene();
	virtual void onLoad();
	virtual void onUnLoad();
	virtual void onUpdate(double i_dt_s);
	virtual void onFixedUpdate(double i_fixed_dt_s);
	bool destroyGameObject(class GameObject* i_game_object);
	const std::vector<class GameObject*>& getGameObjectList()const;
	const GameManager& getGameManager()const;
	void setPlayerController(PlayerController* i_pc);
	template<typename T, typename... Args>
	T* spawnGameObject(Args&&... i_args) {
		static_assert(std::is_base_of_v<GameObject, T>,
			"T must derive from GameObject");
		auto game_object = new T(std::forward<Args>(i_args)...);
		m_game_object_list.push_back(game_object);
		return game_object;
	}
private:
	GameManager& m_game_mgr;
	std::vector<class GameObject*> m_game_object_list;
	PlayerController* m_player_controller = nullptr;
};
