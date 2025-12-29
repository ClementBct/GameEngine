#pragma once
#include "SoundComponent.h"
class Sound2DComponent : public SoundComponent
{
public :
	Sound2DComponent(class GameObject& i_owner, const std::string& i_path);
	void play() override;
};

