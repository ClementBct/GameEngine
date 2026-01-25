#pragma once

#include "Scene/MainScene.h"

#include "GameObject/Robot.h"
#include "GameObject/Ground.h"

MainScene::MainScene(GameManager& i_game_mgr) : Scene(i_game_mgr){
	m_robot = new Robot(*this);
	m_ground = new Ground(*this);

}