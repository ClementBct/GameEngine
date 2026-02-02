#pragma once

#include "Engine/System/System.h"

#include <vector>

class UISystem : public System
{
public:
	UISystem();
	~UISystem();
	void onUpdate(double i_dt_s) override;
	void setCurrentUserInterface(class UserInterface* i_user_interface);
	class UserInterface* getCurrentUserInterface();
protected:
private:
	class UserInterface* m_active_user_interface = nullptr;
	std::vector<UserInterface*> m_visible_user_interface; //need futur implementation
};

