#pragma once

#include <vector>
#include <string>

class Entity
{
public:
	Entity();
	virtual ~Entity();
	/**
	 * @brief Callback called when object start in the world
	 */
	virtual void onStart() = 0;
	/**
	 * @brief Callback called each frame
	 * @param i_delta_time_s the time since the last frame
	 */
	virtual void onUpdate(double i_delta_time_s) = 0;
	/**
	 * @brief Add a component to the game object
	 * @param i_component the component to add
	 * @return the component id
	 */
	size_t addComponent(class Component* i_component);
	/**
	 * @brief Get a component by is ID
	 * @tparam T
	 * @param i_id the id to look for
	 * @return the component if found, nullptr otherwise
	 */
	template<typename T>
	T* getComponentById(size_t i_id);
	// Récupérer le premier component d'un type
	template<typename T>
	T* getComponent();

	// Récupérer tous les components d'un type
	template<typename T>
	std::vector<T*> getComponents();

	void removeComponent(class Component* i_component);
	/**
	 * @brief Get all the component of the game object.
	 * @return Vector with all component
	 */
	std::vector<class Component*> getComponentList();
	template<typename T>
	bool hasComponent();
protected:
private:
	size_t m_next_component_id = 0;
	std::vector<class Component*> m_component_list;
};

template<typename T>
T* Entity::getComponentById(size_t i_id)
{
	for (auto component : m_component_list) {
		if (component->getComponentId() == i_id) {
			return dynamic_cast<T*>(component);
		}
	}
	return nullptr;
}

template<typename T>
T* Entity::getComponent()
{
	for (auto component : m_component_list) {
		T* casted_component = dynamic_cast<T*>(component);
		if (casted_component) {
			return casted_component;
		}
	}
	return nullptr;
}

template<typename T>
std::vector<T*> Entity::getComponents()
{
	std::vector<T*> components;
	for (auto component : m_component_list) {
		T* casted_component = dynamic_cast<T*>(component);
		if (casted_component) {
			components.push_back(casted_component);
		}
	}
	return components;
}

template<typename T>
inline bool Entity::hasComponent()
{
	return false;
}
