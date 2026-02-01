#pragma once

#include "Engine/UI/Widget/UIWidget.h"

class UIButton : public UIWidget
{
public:
	UIButton(const std::string& i_name, UIWidget* i_parent = nullptr);
	~UIButton();
protected:
private:
};