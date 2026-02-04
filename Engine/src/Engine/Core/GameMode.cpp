#include "Engine/Core/GameMode.h"

GameMode::GameMode() {
}
GameMode::~GameMode() {

}
PlayerController* GameMode::getPlayerController() {
	return m_pc;
}

void GameMode::setPlayerController(PlayerController* i_pc) {
	m_pc = i_pc;
}
Scene* GameMode::getScene() {
	return m_scene;
}
void GameMode::setScene(Scene* i_scene) {
	m_scene = i_scene;
}
Actor* GameMode::getActor() {
	return m_pawn;
}
void GameMode::setActor(Actor* i_actor) {
	m_pawn = i_actor;
}