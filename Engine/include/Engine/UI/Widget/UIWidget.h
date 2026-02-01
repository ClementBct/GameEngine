#pragma once

#include <vector>
#include <string>

class UIWidget
{
public:
	UIWidget(const std::string& i_name, UIWidget* i_parent = nullptr);
	virtual ~UIWidget();
	UIWidget* getParent();
	const std::string& getName();
protected:
	UIWidget* m_parent = nullptr;
	//void addComponent(class UIComponent* i_comp);
private:
	std::string m_name;
	std::vector<UIWidget*> m_childs_list;
	std::vector<class UIComponent*> m_comp_list;
};