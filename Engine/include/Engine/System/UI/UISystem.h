#pragma once

#include "Engine/System/System.h"

class UISystem : public System
{
public:
	UISystem();
	~UISystem();
	void onUpdate(double i_dt_s) override;
	void setCurrentUserInterface(class UserInterface* i_user_interface);
protected:
private:
	class UserInterface* m_active_user_interface = nullptr;
};

