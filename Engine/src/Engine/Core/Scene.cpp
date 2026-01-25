#include "Engine/Core/Scene.h"
#include "Engine/Core/GameManager.h"
#include "Engine/ECS/GameObject.h"

#include <algorithm>

Scene::Scene(GameManager& i_game_mgr) : m_game_mgr(i_game_mgr) {
	m_game_mgr.addScene(this);
}

Scene::~Scene() {
	//remove scene from game manager
}

void Scene::addGameObject(GameObject* i_game_object) {
	m_game_object_list.push_back(i_game_object);
}
void Scene::removeGameObject(GameObject* i_game_object) {
	auto it = std::find(m_game_object_list.begin(), m_game_object_list.end(), i_game_object);
	if (it != m_game_object_list.end()) {
		std::iter_swap(it, m_game_object_list.end() - 1);
		m_game_object_list.pop_back();
	}
}
std::vector<GameObject*>& Scene::getGameObjectList() {
	return m_game_object_list;
}

const GameManager& Scene::getGameManager() const{
	return m_game_mgr;
}

void Scene::onLoad() {

}