#include "Engine/System/UI/UISystem.h"
#include "Engine/UI/UserInterface.h"

UISystem::UISystem() {

}

UISystem::~UISystem() {

}

void UISystem::onUpdate(double i_dt_s) {
	(void)i_dt_s;
	if (m_active_user_interface) {
		m_active_user_interface->onUpdate(i_dt_s);
	}
}


void UISystem::setCurrentUserInterface(UserInterface* i_user_interface) {
	m_active_user_interface = i_user_interface;
}

UserInterface* UISystem::getCurrentUserInterface() {
	return m_active_user_interface;
}