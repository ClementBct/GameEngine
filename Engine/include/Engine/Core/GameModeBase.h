#pragma once

#include <string>

class Scene;
class PlayerController;
class Actor;

class GameModeBase {

public:
    GameModeBase();
	virtual ~GameModeBase();
	const std::string getName();
protected:
	Scene* default_scene = nullptr;
	PlayerController* default_pc = nullptr;
	Actor* default_pawn = nullptr;
private:

};