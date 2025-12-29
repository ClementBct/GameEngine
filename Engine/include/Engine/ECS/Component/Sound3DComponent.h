#pragma once
#include "SoundComponent.h"
class Sound3DComponent : public SoundComponent
{
public:
	Sound3DComponent(class GameObject& i_owner, const std::string& i_path);
	void play() override;
};

