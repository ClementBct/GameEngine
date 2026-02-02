#include "Engine/Core/Scene.h"
#include "Engine/Core/GameManager.h"
#include "Engine/ECS/GameObject.h"

#include <algorithm>

Scene::Scene(GameManager& i_game_mgr) : m_game_mgr(i_game_mgr) {
}

Scene::~Scene() {
	for (auto game_object : m_game_object_list) {
		delete game_object;
	}
	m_game_object_list.clear();
}

void onLoad() {

}
void onUnLoad() {

}
bool Scene::destroyGameObject(GameObject* i_game_object) {
	auto it = std::find(m_game_object_list.begin(), m_game_object_list.end(), i_game_object);
	if (it != m_game_object_list.end()) {
		std::iter_swap(it, m_game_object_list.end() - 1);
		m_game_object_list.pop_back();
		return true;
	}
	return false;
}
const std::vector<GameObject*>& Scene::getGameObjectList() const{
	return m_game_object_list;
}

const GameManager& Scene::getGameManager() const{
	return m_game_mgr;
}

void Scene::onLoad() {

}
void Scene::onUnLoad() {

}

void Scene::onUpdate(double i_dt_s) {
	for (auto game_object : m_game_object_list) {
		game_object->onUpdate(i_dt_s);
	}
}

void Scene::onFixedUpdate(double i_fixed_dt_s) {
	(void)i_fixed_dt_s;
}

void Scene::setPlayerController(PlayerController* i_player_controler) {
	m_player_controller = i_player_controler;
}