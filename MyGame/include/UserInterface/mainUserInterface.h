#include "Engine/UI/UserInterface.h"

class MainUserInterface : public UserInterface {
public:
	MainUserInterface(class GameObject& i_owner);
protected:
private:
	class UIImage* m_img_widget = nullptr;
};