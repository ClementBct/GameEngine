#include "Engine/UI/UserInterface.h"
#include "Engine/ECS/GameObject.h"
#include "Engine/UI/Widget/UIWidget.h"

//tempo
#include <print>

UserInterface::UserInterface(GameObject& i_owner, const std::string& i_name) : m_owner(i_owner), m_name(i_name){

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