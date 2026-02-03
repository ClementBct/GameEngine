#include "Engine/UI/UserInterface.h"
#include "Engine/ECS/PlayerController.h"
#include "Engine/Core/RessourceLoader.h"
#include "Engine/UI/Widget/UIWidget.h"

#include "Engine/Utils/Demangler.h"

#include <typeinfo>
#include <string>
//tempo
#include <print>

UserInterface::UserInterface(PlayerController& i_pc, RessourceLoader& i_ressource_loader) : m_pc(i_pc), m_ressource_loader(i_ressource_loader){

}

const std::string UserInterface::getName() {
	std::string name = typeid(*this).name();
	return demangle(name);
}

UserInterface::~UserInterface() {
	for (auto widget : m_widget_list) {
		delete widget;
	}
	m_widget_list.clear();
}

void UserInterface::onUpdate(double i_dt_s) {
	(void)i_dt_s;
}

void UserInterface::removeWidget(UIWidget* i_widget) {
	auto it = std::find(m_widget_list.begin(), m_widget_list.end(), i_widget);
	if (it != m_widget_list.end()) {
		m_widget_list.erase(it);
	}
}
const std::vector<UIWidget*>& UserInterface::getWidgetList() const {
	return m_widget_list;
}