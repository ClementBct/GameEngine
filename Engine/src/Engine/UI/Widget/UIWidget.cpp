#include "Engine/UI/Widget/UIWidget.h"
#include "Engine/UI/Component/UIComponent.h"

UIWidget::UIWidget(const std::string& i_name, UIWidget* i_parent) : m_name(i_name), m_parent(i_parent) {

}

UIWidget::~UIWidget() {

}

UIWidget* UIWidget::getParent() {
	return m_parent;
}

const std::string& UIWidget::getName() {
	return m_name;
}