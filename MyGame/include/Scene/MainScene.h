#include "Engine/Core/Scene.h"

class MainScene : public Scene {
public :
	MainScene(class GameManager& i_game_mgr);
private :
	class Robot* m_robot;
	class Ground* m_ground;
};
