#include "Engine/ECS/Entity.h"
#include "Engine/ECS/Component/Component.h"
#include "Engine/Core/GameManager.h"

#include <print>


Entity::Entity(){
}

Entity::~Entity() {
	// Because ~Components calls RemoveComponent, need a different style loop
	while (!m_component_list.empty()) {
		delete m_component_list.back();
	}
}

void Entity::onUpdate(double i_dt_s) {
	for (auto component : m_component_list) {
		component->onUpdate(i_dt_s);
	}
}

size_t Entity::addComponent(Component* i_component) {
	if (!i_component) {
		std::println("Can't add component: component is not valid");
		return -1;
	}
	size_t id = m_next_component_id++;
	m_component_list.push_back(i_component);
	i_component->setId(id);
	return id;
}

void Entity::removeComponent(Component* i_component)
{
	auto it = std::find(m_component_list.begin(), m_component_list.end(), i_component);
	if (it != m_component_list.end()) {
		m_component_list.erase(it);
	}
}

std::vector<Component*> Entity::getComponentList() {
	return m_component_list;
}
