#include "Engine/System/UI/UISystem.h"
#include "Engine/UI/UserInterface.h"

#include <algorithm>

//tempo
#include <print>
UISystem::UISystem() {

}

UISystem::~UISystem() {

}

void UISystem::onUpdate(double i_dt_s) {
	(void)i_dt_s;
	for (auto ui : m_active_ui_list) {
		ui->onUpdate(i_dt_s);
	}
}

void UISystem::addActiveUserInterface(UserInterface* i_ui) {
	m_active_ui_list.push_back(i_ui);
	std::println("{}", i_ui->getName());
}

bool UISystem::removeActiveUserInterface(UserInterface* i_ui) {
	auto it = std::find(m_active_ui_list.begin(), m_active_ui_list.end(), i_ui);
	if (it != m_active_ui_list.end()) {
		std::iter_swap(it, m_active_ui_list.end() - 1);
		m_active_ui_list.pop_back();
		return true;
	}
	return false;
}

std::vector<UserInterface*>& UISystem::getActiveUserInterface() {
	return m_active_ui_list;
}