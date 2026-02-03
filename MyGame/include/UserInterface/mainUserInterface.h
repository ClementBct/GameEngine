#include "Engine/UI/UserInterface.h"

class PlayerController;
class RessourceLoader;

class MainUserInterface : public UserInterface {
public:
	MainUserInterface(PlayerController& i_pc, RessourceLoader& i_ressource_loader);
protected:
private:
	class UIImage* m_img_widget = nullptr;
};