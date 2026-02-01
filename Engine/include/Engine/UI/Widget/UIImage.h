#pragma once

#include "Engine/UI/Widget/UIWidget.h"

class UIImage : public UIWidget
{
public:
	UIImage(const std::string& i_name, UIWidget* i_parent = nullptr);
	~UIImage();
	void setTexture(class Texture* i_texture);
	class Texture* getTexture();
protected:
private:
	class Texture* m_img_texture = nullptr;
};