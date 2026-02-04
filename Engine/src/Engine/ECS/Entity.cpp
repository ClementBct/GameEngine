#include "Engine/ECS/Entity.h"
#include "Engine/ECS/Component/Component.h"
#include "Engine/Core/GameManager.h"

#include "Engine/Utils/Demangler.h"

#include <print>


Entity::Entity(){
}

Entity::~Entity() {
	for (auto comp : m_component_list) {
		delete comp;
	}
	m_component_list.clear();
}

void Entity::onUpdate(double i_dt_s) {
	for (auto component : m_component_list) {
		component->onUpdate(i_dt_s);
	}
}

void Entity::onFixedUpdate(double i_fixed_dt_s) {
	for (auto component : m_component_list) {
		component->onUpdate(i_fixed_dt_s);
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

const std::string Entity::getName() {
	std::string name = typeid(*this).name();
	return demangle(name);
}

void Entity::destroyComponent(Component* i_comp) {
	auto it = std::find(m_component_list.begin(), m_component_list.end(), i_comp);
	if (it != m_component_list.end()) {
		delete* it;
		m_component_list.erase(it);
	}
}

std::vector<Component*>& Entity::getComponentList() {
	return m_component_list;
}
