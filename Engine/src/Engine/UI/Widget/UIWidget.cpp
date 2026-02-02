#include "Engine/UI/Widget/UIWidget.h"
#include "Engine/UI/Component/UIComponent.h"
#include "Engine/UI/Component/UITransform.h"

UIWidget::UIWidget(const std::string& i_name, UIWidget* i_parent) : m_name(i_name), m_parent(i_parent) {
	m_transform = new UITransform(*this);
}

UIWidget::~UIWidget() {
	delete m_transform;
}

Texture* UIWidget::getTexture() {
	return nullptr;
}

UIWidget* UIWidget::getParent() {
	return m_parent;
}

const std::string& UIWidget::getName() {
	return m_name;
}