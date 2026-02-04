#pragma once

class Scene;
class PlayerController;
class Actor;

class GameMode {
public:
	GameMode();
	virtual ~GameMode();
	PlayerController* getPlayerController();
	void setPlayerController(PlayerController* i_pc);
	Scene* getScene();
	void setScene(Scene* i_scene);
	Actor* getActor();
	void setActor(Actor* i_actor);
protected:
	Scene* m_scene = nullptr;
	PlayerController* m_pc = nullptr;
	Actor* m_pawn = nullptr;
private:
};