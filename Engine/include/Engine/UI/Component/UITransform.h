#pragma once

#include "Engine/Utils/Math.h"
#include "Engine/UI/Component/UIComponent.h"

class UITransform : public UIComponent
{
public:
	UITransform(class UIWidget& i_parent);
	Vector2D position = { 0.0f,0.0f };
	Vector2D scale = { 1.0f,1.0f };
	float rotation = 0.0f;
protected:
private:
	Vector2D m_relative_screen_location = { 0.0f,0.0f };
};