#pragma once

#include <vector>
#include <string>
#include <memory>

class UserInterface
{
public:
	UserInterface(class GameObject& i_owner,const std::string& i_name);
	virtual ~UserInterface();
	virtual void onUpdate(double i_dt_s);
	void addWidget(class UIWidget* i_widget);
	void removeWidget(class UIWidget* i_widget);
	const std::vector<UIWidget*>& getWidgetList() const;

	template<typename T, typename... Args>
	T* createWidget(Args&&... i_args) {
		static_assert(std::is_base_of_v<UIWidget, T>,
			"T must derive from UIWidget");

		auto widget = new T(std::forward<Args>(i_args)...);
		m_widget_list.push_back(widget);
		return widget;
	}

protected:
	class GameObject& m_owner;
private:
	std::vector<UIWidget*> m_widget_list;
	std::string m_name;
};