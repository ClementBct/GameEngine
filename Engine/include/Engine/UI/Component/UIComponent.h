#include "Engine/Utils/Math.h"

struct UITransform {
	Vector2D position = { 0.0 ,0.0 };
	Vector2D scale = { 1.0 ,1.0 };
	Vector2D anchor = { 0.0 ,0.0 };
	int z_index;
};


struct UIInteractable {
	bool hovered  = false; 
	bool pressed = false;
	bool clicked = false;
};