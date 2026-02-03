#pragma once

#include <vector>

class UIComponent
{
public:
	UIComponent(class UIWidget& i_parent);
	virtual ~UIComponent();
	UIWidget& getParent();
protected:
	UIWidget& m_parent;
private:
};